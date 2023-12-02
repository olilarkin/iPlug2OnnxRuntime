# iPlug2OnnxRuntime

Machine Learning Audio plug-in/App example using [iPlug2](https://github.com/iPlug2/iPlug2) and [Microsoft ONNX Runtime](https://github.com/microsoft/onnxruntime).

This example processes an LSTM Neural Network Model trained using Steve Atkinson's [Neural Amp Modeler](https://github.com/sdatkinson/neural-amp-modeler). The C++ code to run this model is found in [LSTMModelInference.h](iPlug2OnnxRuntime/LSTMModelInference.h). The model itself is in `ort-builder/model.onnx`, and converted to .ort format and serialized to a bin2c resource in `ort-builder/model/model.ort.h`. The project links to customised ONNX Runtime static libs which are pruned to contain only the operators and types required for a particular model, only including support for inference using the CPU. ORT is linked statically to make the audio plug-in more portable. These libs are created with a separate repo [ort-builder](https://github.com/olilarkin/ort-builder/), which can be used to customize the libs for your model, and to add support for e.g. GPU inference.

It should compile for macOS, iOS and Windows.

For Windows, you'll need to unzip the onnxruntime.lib in `/ort-builder/libs/win-x86_64/MinSizeRel`. If you need to build the Debug target, you'll need
to compile the debug build of onnxruntime.lib (not included due to its size).

License: MIT

<img src="https://user-images.githubusercontent.com/655662/221144736-05bfbe14-034b-4902-a8b5-49ce0096d553.png" width="40%"/>

<img src="https://user-images.githubusercontent.com/655662/221148599-b500737e-005f-4984-96d5-cc2009e4eee2.png" width="40%"/>

