#pragma once

#include "IPlug_include_in_plug_hdr.h"
#include "LSTMModelInference.h"

#include "queue.h"

const int kNumPresets = 1;

enum EParams
{
  kGain = 0,
  kNumParams
};

using namespace iplug;
using namespace igraphics;

class iPlug2OnnxRuntime final : public Plugin
{
public:
  iPlug2OnnxRuntime(const InstanceInfo& info);

  void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;
  
  IGraphics* CreateGraphics() override;
  void LayoutUI(IGraphics* pGraphics) override;
  
private:
  WDL_TypedQueue<float> mInputQueues[1];
  WDL_TypedQueue<float> mOutputQueues[1];
  
  LSTMModelInference mInference;
};
