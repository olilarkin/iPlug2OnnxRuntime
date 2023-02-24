# iPlug2OnnxRuntime

Machine Learning Audio plug-in/App example using [iPlug2](https://github.com/iPlug2/iPlug2) and [Microsoft ONNX Runtime](https://github.com/microsoft/onnxruntime).

This example processes an LSTM Neural Network Model trained using Steve Atkinson's [Neural Amp Modeler](https://github.com/sdatkinson/neural-amp-modeler).

It uses customised ONNX Runtime static libs which are pruned to contain only the operators and types required for a particular model, and only including support for inference using the CPU. ORT is linked statically to make the audio plug-in more portable.

These libs are created with a separate repo [ort-builder](https://github.com/olilarkin/ort-builder/), which can be used to customize the libs for your model, and to add support for e.g. GPU inference.

It should compile for macOS, iOS. Windows & WASM support coming soon!

License: MIT

<img src="https://user-images.githubusercontent.com/655662/221144736-05bfbe14-034b-4902-a8b5-49ce0096d553.png" width="40%"/>

<img src="https://user-images.githubusercontent.com/655662/221148599-b500737e-005f-4984-96d5-cc2009e4eee2.png" width="40%"/>

