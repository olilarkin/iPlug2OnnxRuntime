
#include <TargetConditionals.h>
#if TARGET_OS_IOS == 1
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
#endif

#define IPLUG_AUVIEWCONTROLLER IPlugAUViewController_viPlug2OnnxRuntime
#define IPLUG_AUAUDIOUNIT IPlugAUAudioUnit_viPlug2OnnxRuntime
#import <iPlug2OnnxRuntimeAU/IPlugAUViewController.h>
#import <iPlug2OnnxRuntimeAU/IPlugAUAudioUnit.h>

//! Project version number for iPlug2OnnxRuntimeAU.
FOUNDATION_EXPORT double iPlug2OnnxRuntimeAUVersionNumber;

//! Project version string for iPlug2OnnxRuntimeAU.
FOUNDATION_EXPORT const unsigned char iPlug2OnnxRuntimeAUVersionString[];

@class IPlugAUViewController_viPlug2OnnxRuntime;
