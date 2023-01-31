#include "iPlug2OnnxRuntime.h"
#include "IPlug_include_in_plug_src.h"

#include "IControls.h"

iPlug2OnnxRuntime::iPlug2OnnxRuntime(const InstanceInfo& info)
: iplug::Plugin(info, MakeConfig(kNumParams, kNumPresets))
{
  GetParam(kGain)->InitDouble("Gain", 0., 0., 100.0, 0.01, "%");
}

IGraphics* iPlug2OnnxRuntime::CreateGraphics()
{
  return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS,
                      GetScaleForScreen(PLUG_WIDTH, PLUG_HEIGHT));
}

void iPlug2OnnxRuntime::LayoutUI(IGraphics* pGraphics)
{
  pGraphics->AttachCornerResizer(EUIResizerMode::Scale, false);
  pGraphics->AttachPanelBackground(COLOR_WHITE);
  pGraphics->LoadFont("Roboto-Regular", ROBOTO_FN);
  const auto b = pGraphics->GetBounds().GetPadded(-10);
  const auto onnxLogo = pGraphics->LoadSVG(ONNX_FN);
  pGraphics->AttachControl(new ISVGControl(b.GetFromTRHC(100, 50), onnxLogo));
  pGraphics->AttachControl(new IVKnobControl(b.GetCentredInside(100), kGain));
}

void iPlug2OnnxRuntime::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
  auto subFrameSize = LSTMModelInference::kMaxBufferSize;
  
  if ((nFrames % subFrameSize == 0)) /* divisible by frame size */
  {
    for (int frame=0; frame<nFrames/subFrameSize; frame++)
    {
      float* frameInput = &inputs[0][frame*subFrameSize];
      float* frameOutput = &outputs[0][frame*subFrameSize];
      mInference.ProcessBlock(frameInput, frameOutput, subFrameSize);
    }
  }
  else // buffer = more latency :-(
  {
    mInputQueues[0].Add(inputs[0], nFrames);
    
    while (mInputQueues[0].Available() >= subFrameSize)
    {
      float* frameInput = mInputQueues[0].Get();
      float* frameOutput = mOutputQueues[0].Add(NULL, subFrameSize);
      mInference.ProcessBlock(frameInput, frameOutput, subFrameSize);
      mInputQueues[0].Advance(subFrameSize);
    }
    
    mInputQueues[0].Compact(); // shuffle input buffers if necessary
    
    if (mOutputQueues[0].Available() < nFrames)
    {
      // if this happens you need to report latency!
    }
    else
    {
      memcpy(outputs[0], mOutputQueues[0].Get(), sizeof(sample) * nFrames);
      mOutputQueues[0].Advance(nFrames);
      mOutputQueues[0].Compact(); // shuffle output buffers
    }
  }

  // Process Gain
  
  const float gain = float(GetParam(kGain)->Value() / 100.0);
    
  for (int s = 0; s < nFrames; s++)
  {
    outputs[0][s] = outputs[0][s] * gain;
    outputs[1][s] = outputs[0][s];
  }
}

#include "model.ort.c"
