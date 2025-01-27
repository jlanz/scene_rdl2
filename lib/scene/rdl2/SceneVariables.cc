// Copyright 2023 DreamWorks Animation LLC
// SPDX-License-Identifier: Apache-2.0


#include <scene_rdl2/common/platform/Platform.h>

#include "SceneVariables.h"

#include "AttributeKey.h"
#include "SceneClass.h"
#include "SceneContext.h"
#include "SceneObject.h"
#include "Types.h"

#include <scene_rdl2/common/except/exceptions.h>
#include <scene_rdl2/render/util/GetEnv.h>

#include <limits>
#include <string>

namespace scene_rdl2 {
namespace rdl2 {

using math::HalfOpenViewport;
using math::Viewport;

AttributeKey<Float> SceneVariables::sMinFrameKey;
AttributeKey<Float> SceneVariables::sMaxFrameKey;
AttributeKey<Float> SceneVariables::sFrameKey;

AttributeKey<SceneObject*> SceneVariables::sCamera;
AttributeKey<SceneObject*> SceneVariables::sDicingCamera;
AttributeKey<SceneObject*> SceneVariables::sLayer;
AttributeKey<SceneObject*> SceneVariables::sAttrExrHeaderAttributes;

AttributeKey<Int>       SceneVariables::sImageWidth;
AttributeKey<Int>       SceneVariables::sImageHeight;
AttributeKey<Float>     SceneVariables::sResKey;
AttributeKey<IntVector> SceneVariables::sApertureWindow;
AttributeKey<IntVector> SceneVariables::sRegionWindow;
AttributeKey<IntVector> SceneVariables::sSubViewport;

AttributeKey<FloatVector> SceneVariables::sMotionSteps;
AttributeKey<Float>       SceneVariables::sFpsKey;
AttributeKey<Float>       SceneVariables::sSceneScaleKey;

AttributeKey<Int>   SceneVariables::sSamplingMode;
AttributeKey<Int>   SceneVariables::sMinAdaptiveSamples;
AttributeKey<Int>   SceneVariables::sMaxAdaptiveSamples;
AttributeKey<Float> SceneVariables::sTargetAdaptiveError;

AttributeKey<Int>   SceneVariables::sPixelSamplesSqrt;
AttributeKey<Int>   SceneVariables::sLightSamplesSqrt;
AttributeKey<Int>   SceneVariables::sBsdfSamplesSqrt;
AttributeKey<Int>   SceneVariables::sBsdfSamplerStrategy;
AttributeKey<Int>   SceneVariables::sBssrdfSamplesSqrt;
AttributeKey<Int>   SceneVariables::sMaxDepth;
AttributeKey<Int>   SceneVariables::sMaxDiffuseDepth;
AttributeKey<Int>   SceneVariables::sMaxGlossyDepth;
AttributeKey<Int>   SceneVariables::sMaxMirrorDepth;
AttributeKey<Int>   SceneVariables::sMaxVolumeDepth;
AttributeKey<Int>   SceneVariables::sMaxPresenceDepth;
AttributeKey<Int>   SceneVariables::sMaxHairDepth;
AttributeKey<Bool>  SceneVariables::sDisableOptimizedHairSampling;
AttributeKey<Int>   SceneVariables::sMaxSubsurfacePerPath;
AttributeKey<Float> SceneVariables::sTransparencyThreshold;
AttributeKey<Float> SceneVariables::sPresenceThreshold;
AttributeKey<Float> SceneVariables::sRussianRouletteThreshold;
AttributeKey<Bool>  SceneVariables::sLockFrameNoise;

AttributeKey<Float> SceneVariables::sSampleClampingValue;
AttributeKey<Int>   SceneVariables::sSampleClampingDepth;
AttributeKey<Float> SceneVariables::sRoughnessClampingFactor;

AttributeKey<Float> SceneVariables::sVolumeQuality;
AttributeKey<Float> SceneVariables::sVolumeShadowQuality;
AttributeKey<Int>   SceneVariables::sVolumeIlluminationSamples;
AttributeKey<Float> SceneVariables::sVolumeOpacityThreshold;
AttributeKey<Int>   SceneVariables::sVolumeOverlapMode;
AttributeKey<Float> SceneVariables::sVolumeAttenuationFactor;
AttributeKey<Float> SceneVariables::sVolumeContributionFactor;
AttributeKey<Float> SceneVariables::sVolumePhaseAttenuationFactor;

AttributeKey<Bool> SceneVariables::sPathGuideEnable;

AttributeKey<Float> SceneVariables::sTextureBlur;
AttributeKey<Float> SceneVariables::sPixelFilterWidth;
AttributeKey<Int>   SceneVariables::sPixelFilterType;

AttributeKey<Int>          SceneVariables::sDeepFormat;
AttributeKey<Float>        SceneVariables::sDeepCurvatureTolerance;
AttributeKey<Float>        SceneVariables::sDeepZTolerance;
AttributeKey<Int>          SceneVariables::sDeepVolCompressionRes;
AttributeKey<StringVector> SceneVariables::sDeepIDAttributeNames;
AttributeKey<Int>          SceneVariables::sDeepMaxLayers;
AttributeKey<Float>        SceneVariables::sDeepLayerBias;

AttributeKey<Int>  SceneVariables::sTextureCacheSizeMb;
AttributeKey<Int>  SceneVariables::sTextureFileHandleCount;
AttributeKey<Bool> SceneVariables::sFastGeomUpdate;

AttributeKey<Bool>   SceneVariables::sCheckpointActive;
AttributeKey<Float>  SceneVariables::sCheckpointInterval;
AttributeKey<Int>    SceneVariables::sCheckpointQualitySteps;
AttributeKey<Float>  SceneVariables::sCheckpointTimeCap;
AttributeKey<Int>    SceneVariables::sCheckpointSampleCap;
AttributeKey<Bool>   SceneVariables::sCheckpointOverwrite;
AttributeKey<Int>    SceneVariables::sCheckpointMode;
AttributeKey<Int>    SceneVariables::sCheckpointStartSPP;
AttributeKey<Bool>   SceneVariables::sCheckpointBgWrite;
AttributeKey<String> SceneVariables::sCheckpointPostScript;
AttributeKey<Int>    SceneVariables::sCheckpointTotalFiles;
AttributeKey<Int>    SceneVariables::sCheckpointMaxBgCache;
AttributeKey<Float>  SceneVariables::sCheckpointMaxSnapshotOverhead;
AttributeKey<Float>  SceneVariables::sCheckpointSnapshotInterval;

AttributeKey<Bool>   SceneVariables::sResumableOutput;
AttributeKey<Bool>   SceneVariables::sResumeRender;
AttributeKey<String> SceneVariables::sOnResumeScript;

AttributeKey<Bool> SceneVariables::sTwoStageOutput;

AttributeKey<Bool> SceneVariables::sEnableMotionBlur;
AttributeKey<Bool> SceneVariables::sEnableDof;
AttributeKey<Bool> SceneVariables::sEnableMaxGeomResolution;
AttributeKey<Int>  SceneVariables::sMaxGeomResolution;
AttributeKey<Bool> SceneVariables::sEnableDisplacement;
AttributeKey<Bool> SceneVariables::sEnableSSS;
AttributeKey<Bool> SceneVariables::sEnableShadowing;
AttributeKey<Bool> SceneVariables::sEnablePresenceShadows;
AttributeKey<Bool> SceneVariables::sLightsVisibleInCameraKey;
AttributeKey<Bool> SceneVariables::sPropagateVisibilityBounceType;
AttributeKey<Int>  SceneVariables::sShadowTerminatorFix;

AttributeKey<Int>    SceneVariables::sThreads;
AttributeKey<Int>    SceneVariables::sMachineId;
AttributeKey<Int>    SceneVariables::sNumMachines;
AttributeKey<Int>    SceneVariables::sTaskDistributionType;
AttributeKey<Bool>   SceneVariables::sInteractiveKey;
AttributeKey<Bool>   SceneVariables::sProgressiveKey;
AttributeKey<Int>    SceneVariables::sBatchTileOrder;
AttributeKey<Int>    SceneVariables::sProgressiveTileOrder;
AttributeKey<Int>    SceneVariables::sCheckpointTileOrder;
AttributeKey<String> SceneVariables::sOutputFile;
AttributeKey<String> SceneVariables::sTemporaryDirectory;

AttributeKey<Bool>   SceneVariables::sDebugKey;
AttributeKey<Bool>   SceneVariables::sInfoKey;
AttributeKey<Bool>   SceneVariables::sWarningKey;
AttributeKey<Bool>   SceneVariables::sErrorKey;
AttributeKey<Rgb>    SceneVariables::sFatalColor;
AttributeKey<String> SceneVariables::sStatsFile;
AttributeKey<Bool>   SceneVariables::sAthenaDebug;

AttributeKey<IntVector> SceneVariables::sDebugPixel;
AttributeKey<String>    SceneVariables::sDebugRaysFile;
AttributeKey<IntVector> SceneVariables::sDebugRaysPrimaryRange;
AttributeKey<IntVector> SceneVariables::sDebugRaysDepthRange;
AttributeKey<Int>       SceneVariables::sDebugConsole;
AttributeKey<Bool>      SceneVariables::sValidateGeometry;

SceneVariables::SceneVariables(const SceneClass& sceneClass, const std::string& name)
: Parent(sceneClass, name)
{
}

SceneObjectInterface
SceneVariables::declare(SceneClass& sceneClass)
{
    constexpr int minIntVal = std::numeric_limits<int>::lowest();

    auto interface = Parent::declare(sceneClass);

    sMinFrameKey = sceneClass.declareAttribute<Float>("min_frame", 0.0f, {"min frame"});
    sceneClass.setMetadata(sMinFrameKey, "label", "min frame");

    sMaxFrameKey = sceneClass.declareAttribute<Float>("max_frame", 0.0f, {"max frame"});
    sceneClass.setMetadata(sMaxFrameKey, "label", "max frame");

    sFrameKey = sceneClass.declareAttribute<Float>("frame", 0.0f);

    sCamera = sceneClass.declareAttribute<SceneObject*>("camera", FLAGS_NONE, INTERFACE_CAMERA);
    sDicingCamera = sceneClass.declareAttribute<SceneObject*>("dicing_camera", FLAGS_NONE, INTERFACE_CAMERA);

    sLayer = sceneClass.declareAttribute<SceneObject*>("layer", FLAGS_NONE, INTERFACE_LAYER);

    sAttrExrHeaderAttributes = sceneClass.declareAttribute<SceneObject*>("exr_header_attributes",
        FLAGS_NONE,
        INTERFACE_METADATA,
        {"exr header attributes"});
    sceneClass.setMetadata(sAttrExrHeaderAttributes, "label", "exr header attributes");
    sceneClass.setMetadata(sAttrExrHeaderAttributes,
        SceneClass::sComment,
        "Metadata that is passed directly to the exr header. Format: {\"name\", \"type\", \"value\"}");

    sImageWidth = sceneClass.declareAttribute<Int>("image_width", Int(1920), {"image width"});
    sceneClass.setMetadata(sImageWidth, "label", "image width");

    sImageHeight = sceneClass.declareAttribute<Int>("image_height", Int(1080), {"image height"});
    sceneClass.setMetadata(sImageHeight, "label", "image height");

    sResKey = sceneClass.declareAttribute<Float>("res", 1.0f);

    IntVector viewportVector = {minIntVal, minIntVal, minIntVal, minIntVal};
    sApertureWindow = sceneClass.declareAttribute<IntVector>("aperture_window", viewportVector, {"aperture window"});
    sceneClass.setMetadata(sApertureWindow, "label", "aperture window");
    sceneClass.setMetadata(sApertureWindow,
        SceneClass::sComment,
        "The window of the camera aperture. Overrides image_width and image_height. Ordered as xmin, ymin, xmax, and "
        "ymax, with origin at the bottom-left.");

    sRegionWindow = sceneClass.declareAttribute<IntVector>("region_window", viewportVector, {"region window"});
    sceneClass.setMetadata(sRegionWindow, "label", "region window");
    sceneClass.setMetadata(sRegionWindow,
        SceneClass::sComment,
        "Window that is rendered. Overrides image width / height (and overrides aperture window override). Order: xmin "
        "ymin xmax ymax, with origin at left bottom.");

    // "sub viewport" is defined such that a coordinate of (0, 0) maps to the left,
    // bottom of the region window (i.e. the render buffer).
    sSubViewport = sceneClass.declareAttribute<IntVector>("sub_viewport", viewportVector, {"sub viewport"});
    sceneClass.setMetadata(sSubViewport, "label", "sub viewport");
    sceneClass.setMetadata(sSubViewport,
        SceneClass::sComment,
        "Subviewport of region window. Coordinate (0,0) maps to left, bottom of region window");

    FloatVector defaultMotionSteps = {-1.0f, 0.0f};
    sMotionSteps = sceneClass.declareAttribute<FloatVector>("motion_steps", defaultMotionSteps, {"motion steps"});
    sceneClass.setMetadata(sMotionSteps, "label", "motion steps");
    sceneClass.setMetadata(sMotionSteps, SceneClass::sComment, "frame-relative time offsets for motion sampling");

    sFpsKey = sceneClass.declareAttribute<Float>("fps", 24.0f);

    sSceneScaleKey = sceneClass.declareAttribute<Float>("scene_scale", 0.01f, {"scene scale"});
    sceneClass.setMetadata(sSceneScaleKey, "label", "scene scale");
    sceneClass.setMetadata(sSceneScaleKey,
        SceneClass::sComment,
        "(in meters): one unit in world space = 'scene scale' meters");

    sSamplingMode = sceneClass.declareAttribute<Int>("sampling_mode",
        Int(0),
        rdl2::FLAGS_ENUMERABLE,
        INTERFACE_GENERIC,
        {"sampling mode"});
    sceneClass.setMetadata(sSamplingMode, "label", "sampling mode");
    sceneClass.setEnumValue(sSamplingMode, 0, "uniform");
    sceneClass.setEnumValue(sSamplingMode, 2, "adaptive");
    sceneClass.setMetadata(sSamplingMode,
        SceneClass::sComment,
        "Controls which sampling scheme to use: uniform or adaptive.");

    sMinAdaptiveSamples = sceneClass.declareAttribute<Int>("min_adaptive_samples", Int(16), {"min adaptive samples"});
    sceneClass.setMetadata(sMinAdaptiveSamples, "label", "min adaptive samples");
    sceneClass.setMetadata(sMinAdaptiveSamples,
        SceneClass::sComment,
        "When adaptive sampling is turned on, it's possible that a tile may be mis-classified as having converged "
        "before it has actually converged. This manifests itself as square 8x8 artifacts in the final image. The "
        "higher this value, the less the chance of this happening.");

    sMaxAdaptiveSamples = sceneClass.declareAttribute<Int>("max_adaptive_samples", Int(4096), {"max adaptive samples"});
    sceneClass.setMetadata(sMaxAdaptiveSamples, "label", "max adaptive samples");
    sceneClass.setMetadata(sMaxAdaptiveSamples,
        SceneClass::sComment,
        "When adaptive sampling is turned on, this represents the max number of samples we can throw at a pixel. It's "
        "best to err on the high side since adaptive sampling will cull out samples where they're not needed based on "
        "the target adaptive error, in which case we should rarely hit the max samples value.");

    sTargetAdaptiveError =
        sceneClass.declareAttribute<Float>("target_adaptive_error", Float(10.0), {"target adaptive error"});
    sceneClass.setMetadata(sTargetAdaptiveError, "label", "target adaptive error");
    sceneClass.setMetadata(sTargetAdaptiveError,
        SceneClass::sComment,
        "When adaptive sampling is turned on, this represents the desired quality of the output images. Lower values "
        "will give higher quality but take longer to render. Higher values will give lower quality but render "
        "quicker.");

    sPixelSamplesSqrt = sceneClass.declareAttribute<Int>("pixel_samples", Int(8), {"pixel samples"});
    sceneClass.setMetadata(sPixelSamplesSqrt, "label", "pixel samples");
    sceneClass.setMetadata(sPixelSamplesSqrt,
        SceneClass::sComment,
        "The square root of the number of primary samples taken for each pixel in uniform sampling mode. For example, "
        "a value of 4 will result in 4*4 = 16 uniform pixel samples.");

    sLightSamplesSqrt = sceneClass.declareAttribute<Int>("light_samples", Int(2), {"light samples"});
    sceneClass.setMetadata(sLightSamplesSqrt, "label", "light samples");

    sBsdfSamplesSqrt = sceneClass.declareAttribute<Int>("bsdf_samples", Int(2), {"bsdf samples"});
    sceneClass.setMetadata(sBsdfSamplesSqrt, "label", "bsdf samples");

    sBsdfSamplerStrategy = sceneClass.declareAttribute<Int>("bsdf_sampler_strategy",
        Int(BsdfSamplerStrategy::MULTI_SAMPLE),
        rdl2::FLAGS_ENUMERABLE);
    sceneClass.setEnumValue(sBsdfSamplerStrategy, Int(BsdfSamplerStrategy::MULTI_SAMPLE), "multi-sample");
    sceneClass.setEnumValue(sBsdfSamplerStrategy, Int(BsdfSamplerStrategy::ONE_SAMPLE), "one-sample");
    sceneClass.setEnumValue(sBsdfSamplerStrategy, Int(BsdfSamplerStrategy::ONE_LOBE), "one-lobe");
    sceneClass.setMetadata(sBsdfSamplerStrategy,
        SceneClass::sComment,
        "Indirect sampling and evaluation strategy: all lobes using one path segment per lobe (multi-sample), all "
        "lobes using one shared path segment (one-sample), or one lobe.");

    sBssrdfSamplesSqrt = sceneClass.declareAttribute<Int>("bssrdf_samples", Int(2), {"bssrdf samples"});
    sceneClass.setMetadata(sBssrdfSamplesSqrt, "label", "bssrdf samples");

    sMaxDepth = sceneClass.declareAttribute<Int>("max_depth", Int(5), {"max depth"});
    sceneClass.setMetadata(sMaxDepth, "label", "max depth");

    sMaxDiffuseDepth = sceneClass.declareAttribute<Int>("max_diffuse_depth", Int(2), {"max diffuse depth"});
    sceneClass.setMetadata(sMaxDiffuseDepth, "label", "max diffuse depth");

    sMaxGlossyDepth = sceneClass.declareAttribute<Int>("max_glossy_depth", Int(2), {"max glossy depth"});
    sceneClass.setMetadata(sMaxGlossyDepth, "label", "max glossy depth");

    sMaxMirrorDepth = sceneClass.declareAttribute<Int>("max_mirror_depth", Int(3), {"max mirror depth"});
    sceneClass.setMetadata(sMaxMirrorDepth, "label", "max mirror depth");

    sMaxVolumeDepth = sceneClass.declareAttribute<Int>("max_volume_depth", Int(1), {"max volume depth"});
    sceneClass.setMetadata(sMaxVolumeDepth, "label", "max volume depth");

    sMaxPresenceDepth = sceneClass.declareAttribute<Int>("max_presence_depth", Int(16), {"max presence depth"});
    sceneClass.setMetadata(sMaxPresenceDepth, "label", "max presence depth");

    sMaxHairDepth = sceneClass.declareAttribute<Int>("max_hair_depth", Int(5));
    sceneClass.setMetadata(sMaxHairDepth, "label", "max hair depth");

    sDisableOptimizedHairSampling = sceneClass.declareAttribute<Bool>("disable_optimized_hair_sampling", Bool(false));
    sceneClass.setMetadata(sDisableOptimizedHairSampling, "label", "disable optimized hair sampling");
    sceneClass.setMetadata(sDisableOptimizedHairSampling,
        SceneClass::sComment,
        "Forces all hair materials to sample each hair BSDF lobe independently. This will enable the LPE label syntax "
        "for 'hair R', 'hair TT', 'hair TRT' and 'hair TRRT ' but will result in slower rendering");

    sMaxSubsurfacePerPath = sceneClass.declareAttribute<Int>("max_subsurface_per_path", Int(1));
    sceneClass.setMetadata(sMaxSubsurfacePerPath, "label", "max subsurface per path");

    sRussianRouletteThreshold =
        sceneClass.declareAttribute<Float>("russian_roulette_threshold", Float(0.0375), {"russian roulette threshold"});
    sceneClass.setMetadata(sRussianRouletteThreshold, "label", "russian roulette threshold");

    sTransparencyThreshold =
        sceneClass.declareAttribute<Float>("transparency_threshold", Float(1.0), {"transparency threshold"});
    sceneClass.setMetadata(sTransparencyThreshold, "label", "transparency threshold");
    sceneClass.setMetadata(sTransparencyThreshold,
        SceneClass::sComment,
        "Defines at which point the accumulated opacity can be considered as opaque, skipping generation of new "
        "transparency rays.");

    sPresenceThreshold = sceneClass.declareAttribute<Float>("presence_threshold", Float(0.999), {"presence threshold"});
    sceneClass.setMetadata(sPresenceThreshold, "label", "presence threshold");
    sceneClass.setMetadata(sPresenceThreshold,
        SceneClass::sComment,
        "Defines at which point the accumulated presence can be considered as opaque, skipping generation of presence "
        "continuation rays.");

    sLockFrameNoise = sceneClass.declareAttribute<Bool>("lock_frame_noise", false, {"lock frame noise"});
    sceneClass.setMetadata(sLockFrameNoise, "label", "lock frame noise");

    sVolumeQuality = sceneClass.declareAttribute<Float>("volume_quality", Float(0.5f), {"volume quality"});
    sceneClass.setMetadata(sVolumeQuality, "label", "volume quality");
    sceneClass.setMetadata(sVolumeQuality,
        SceneClass::sComment,
        "Controls the overall quality of volume rendering. The higher number gives better volume shape detail and more "
        "accurate scattering integration result.");

    sVolumeShadowQuality =
        sceneClass.declareAttribute<Float>("volume_shadow_quality", Float(1.0f), {"volume shadow quality"});
    sceneClass.setMetadata(sVolumeShadowQuality, "label", "volume shadow quality");
    sceneClass.setMetadata(sVolumeShadowQuality,
        SceneClass::sComment,
        "Controls the quality of volume shadow (transmittance). The higher number gives more accurate volume shadow.");

    sVolumeIlluminationSamples =
        sceneClass.declareAttribute<Int>("volume_illumination_samples", Int(4), {"volume illumination samples"});
    sceneClass.setMetadata(sVolumeIlluminationSamples, "label", "volume illumination samples");
    sceneClass.setMetadata(sVolumeIlluminationSamples,
        SceneClass::sComment,
        "Sample number along the ray when computing volume scattering radiance towards the eye. Set to 0 to turn off "
        "volume lighting completely.");

    sVolumeOpacityThreshold =
        sceneClass.declareAttribute<Float>("volume_opacity_threshold", Float(0.995f), {"volume opacity threshold"});
    sceneClass.setMetadata(sVolumeOpacityThreshold, "label", "volume opacity threshold");
    sceneClass.setMetadata(sVolumeOpacityThreshold,
        SceneClass::sComment,
        "As a ray travels through volume regions, it will accumulate the amount of opacity. When the value exceeds "
        "volume opacity threshold the renderer will stop the further volume integration along this ray.");

    sVolumeOverlapMode =
        sceneClass.declareAttribute<Int>("volume_overlap_mode", Int(VolumeOverlapMode::SUM), rdl2::FLAGS_ENUMERABLE);
    sceneClass.setEnumValue(sVolumeOverlapMode, static_cast<int>(VolumeOverlapMode::SUM), "sum");
    sceneClass.setEnumValue(sVolumeOverlapMode, static_cast<int>(VolumeOverlapMode::MAX), "max");
    sceneClass.setEnumValue(sVolumeOverlapMode, static_cast<int>(VolumeOverlapMode::RND), "rnd");
    sceneClass.setMetadata(sVolumeOverlapMode, "label", "volume overlap mode");
    sceneClass.setMetadata(sVolumeOverlapMode,
        SceneClass::sComment,
        "Selects how to handle contributions from overlapping volumes:\n"
        "\t\tsum: add contributions from all volumes\n"
        "\t\tmax: only consider maximum volume based on extinction\n"
        "\t\trnd: randomly choose one value weighted by extinction\n"
        "\t\tWarning: light linking does not work correctly in sum mode.");

    sVolumeAttenuationFactor =
        sceneClass.declareAttribute<Float>("volume_attenuation_factor", Float(0.65f), {"volume attenuation factor"});
    sceneClass.setMetadata(sVolumeAttenuationFactor, "label", "volume attenuation factor");
    sceneClass.setMetadata(sVolumeAttenuationFactor,
        SceneClass::sComment,
        "Controls how volume attenuation gets exponentially scaled down when rendering multiple scattering volumes. "
        "Dialing down the value generally results in more translucent look. This variable is only effective when \"max "
        "volume depth\" is greater than 1");

    sVolumeContributionFactor =
        sceneClass.declareAttribute<Float>("volume_contribution_factor", Float(0.65f), {"volume contribution factor"});
    sceneClass.setMetadata(sVolumeContributionFactor, "label", "volume contribution factor");
    sceneClass.setMetadata(sVolumeContributionFactor,
        SceneClass::sComment,
        "Controls how scattering contribution gets exponentially scaled down when rendering multiple scattering "
        "volumes. Dialing down the value generally results in a darker volume scattering look. This variable is only "
        "effective when \"max volume depth\" is greater than 1");

    sVolumePhaseAttenuationFactor = sceneClass.declareAttribute<Float>("volume_phase_attenuation_factor",
        Float(0.5f),
        {"volume phase attenuation factor"});
    sceneClass.setMetadata(sVolumePhaseAttenuationFactor, "label", "volume phase attenuation factor");
    sceneClass.setMetadata(sVolumePhaseAttenuationFactor,
        SceneClass::sComment,
        "Controls how phase function (anisotropy) gets exponentially scaled down when rendering multiple scattering "
        "volumes. This variable is only effective when \"max volume depth\" is greater than 1");

    sPathGuideEnable = sceneClass.declareAttribute<Bool>("path_guide_enable", false);
    sceneClass.setMetadata(sPathGuideEnable, "label", "path guide enable");
    sceneClass.setMetadata(sPathGuideEnable,
        SceneClass::sComment,
        "Turn on path guiding to handle difficult light transport problems (e.g. caustics) at the cost of increased "
        "memory");

    sSampleClampingValue =
        sceneClass.declareAttribute<Float>("sample_clamping_value", Float(10.0f), {"sample clamping value"});
    sceneClass.setMetadata(sSampleClampingValue, "label", "sample clamping value");
    sceneClass.setMetadata(sSampleClampingValue,
        SceneClass::sComment,
        "Clamp sample radiance values to this maximum value (the feature is disabled if the value is 0.0). Using this "
        "technique reduces fireflies, but is biased.");

    sSampleClampingDepth = sceneClass.declareAttribute<Int>("sample_clamping_depth", Int(1), {"sample clamping depth"});
    sceneClass.setMetadata(sSampleClampingDepth, "label", "sample clamping depth");
    sceneClass.setMetadata(sSampleClampingDepth,
        SceneClass::sComment,
        "Clamp sample values only after the given non-specular ray depth.");

    sRoughnessClampingFactor =
        sceneClass.declareAttribute<Float>("roughness_clamping_factor", Float(0.0), {"roughness clamping factor"});
    sceneClass.setMetadata(sRoughnessClampingFactor, "label", "roughness clamping factor");
    sceneClass.setMetadata(sRoughnessClampingFactor,
        SceneClass::sComment,
        "Clamp material roughness along paths. A value of 1 clamps values to the maximum roughness encountered, while "
        "lower values temper the clamping value. 0 disables the effect. Using this technique reduces fireflies from "
        "indirect caustics but is biased.");

    sTextureBlur = sceneClass.declareAttribute<Float>("texture_blur", Float(0.0), {"texture blur"});
    sceneClass.setMetadata(sTextureBlur, "label", "texture blur");

    sPixelFilterWidth = sceneClass.declareAttribute<Float>("pixel_filter_width", Float(3.0), {"pixel filter width"});
    sceneClass.setMetadata(sPixelFilterWidth, "label", "pixel filter width");
    sceneClass.setMetadata(sPixelFilterWidth,
        SceneClass::sComment,
        "The overall extents, in pixels, of the pixel filter. Larger values will result in softer images.");

    sPixelFilterType = sceneClass.declareAttribute<Int>("pixel_filter",
        Int(1),
        rdl2::FLAGS_ENUMERABLE,
        INTERFACE_GENERIC,
        {"pixel filter"});
    sceneClass.setMetadata(sPixelFilterType, "label", "pixel filter");
    sceneClass.setEnumValue(sPixelFilterType, 0, "box");
    sceneClass.setEnumValue(sPixelFilterType, 1, "cubic b-spline");
    sceneClass.setEnumValue(sPixelFilterType, 2, "quadratic b-spline");
    sceneClass.setMetadata(sPixelFilterType,
        SceneClass::sComment,
        "The type of filter used for filter importance sampling. A box filter with a width of 1 is analogous to "
        "disabling pixel filtering.");

    sDeepFormat = sceneClass.declareAttribute<Int>("deep_format",
        Int(1),
        rdl2::FLAGS_ENUMERABLE,
        INTERFACE_GENERIC,
        {"deep format"});
    sceneClass.setMetadata(sDeepFormat, "label", "deep format");
    sceneClass.setEnumValue(sDeepFormat, 0, "openexr2.0");
    sceneClass.setEnumValue(sDeepFormat, 1, "opendcx2.0");
    sceneClass.setMetadata(sDeepFormat,
        SceneClass::sComment,
        "Deep image format:\n"
        "\t\topenexr2.0: vanilla OpenEXR deep\n"
        "\t\topendcx2.0: DCX abuffer mask encoding");

    sDeepCurvatureTolerance =
        sceneClass.declareAttribute<Float>("deep_curvature_tolerance", Float(45.0), {"deep curvature tolerance"});
    sceneClass.setMetadata(sDeepCurvatureTolerance, "label", "deep curvature tolerance");
    sceneClass.setMetadata(sDeepCurvatureTolerance,
        SceneClass::sComment,
        "Maximum curvature (in degrees) of the deep surface within a pixel before it is split");

    sDeepZTolerance = sceneClass.declareAttribute<Float>("deep_z_tolerance", Float(2.0), {"deep z tolerance"});
    sceneClass.setMetadata(sDeepZTolerance, "label", "deep z tolerance");
    sceneClass.setMetadata(sDeepZTolerance,
        SceneClass::sComment,
        "Maximum range of the deep surface's Z values within a pixel before it is split");

    sDeepVolCompressionRes =
        sceneClass.declareAttribute<Int>("deep_vol_compression_res", Int(10), {"deep vol compression res"});
    sceneClass.setMetadata(sDeepVolCompressionRes, "label", "deep vol compression res");
    sceneClass.setMetadata(sDeepVolCompressionRes,
        SceneClass::sComment,
        "Volume opacity compression resolution.  Lower values gives higher compression.");

    sDeepIDAttributeNames =
        sceneClass.declareAttribute<StringVector>("deep_id_attribute_names", {"deep ID attribute names"});
    sceneClass.setMetadata(sDeepIDAttributeNames, "label", "deep ID attribute names");
    sceneClass.setMetadata(sDeepIDAttributeNames,
        SceneClass::sComment,
        "Names of primitive attributes containing deep IDs");

    sDeepMaxLayers = sceneClass.declareAttribute<Int>("deep_max_layers", Int(1), {"deep max layers"});
    sceneClass.setMetadata(sDeepMaxLayers, "label", "deep max layers");
    sceneClass.setMetadata(sDeepMaxLayers, SceneClass::sComment, "Maximum number of depth layers to output");

    sDeepLayerBias = sceneClass.declareAttribute<Float>("deep_layer_bias", Float(0.1f), {"deep layer bias"});
    sceneClass.setMetadata(sDeepLayerBias, "label", "deep layer bias");
    sceneClass.setMetadata(sDeepLayerBias, SceneClass::sComment, "Minimum distance between deep layers");

    sTextureCacheSizeMb = sceneClass.declareAttribute<Int>("texture_cache_size", Int(4000), {"texture cache size"});
    sceneClass.setMetadata(sTextureCacheSizeMb, "label", "texture cache size");
    sceneClass.setMetadata(sTextureCacheSizeMb,
        SceneClass::sComment,
        "size is in Mb and this is the maximum cache size");

    // Last time we checked, there was a 32k file handle limit per process.
    // Allocate a high maximum for OIIO texture handles.
    sTextureFileHandleCount =
        sceneClass.declareAttribute<Int>("texture_file_handles", Int(24000), {"texture file handles"});
    sceneClass.setMetadata(sTextureFileHandleCount, "label", "texture file handles");
    sceneClass.setMetadata(sTextureFileHandleCount,
        SceneClass::sComment,
        "maximum number of simultaneous open file handles");

    sFastGeomUpdate = sceneClass.declareAttribute("fast_geometry_update", false, {"fast geometry update"});
    sceneClass.setMetadata(sFastGeomUpdate, "label", "fast geometry update");

    // Checkpoint render
    sCheckpointActive = sceneClass.declareAttribute<Bool>("checkpoint_active", false, {"checkpoint active"});
    sceneClass.setMetadata(sCheckpointActive, "label", "checkpoint active");

    sCheckpointInterval =
        sceneClass.declareAttribute<Float>("checkpoint_interval", Float(15.0f), {"checkpoint interval"});
    sceneClass.setMetadata(sCheckpointInterval, "label", "checkpoint interval");
    sceneClass.setMetadata(sCheckpointInterval,
        SceneClass::sComment,
        "Length of time, in minutes, between checkpoint file writes. Time must be greater or equal to 0.1");

    sCheckpointQualitySteps =
        sceneClass.declareAttribute<Int>("checkpoint_quality_steps", Int(2), {"checkpoint quality steps"});
    sceneClass.setMetadata(sCheckpointQualitySteps, "label", "checkpoint quality steps");
    sceneClass.setMetadata(sCheckpointQualitySteps,
        SceneClass::sComment,
        "Steps of quality, internal sampling iteration count, between checkpoint file writes. Value should be equal or "
        "bigger than 1. Uniform sampling case, this steps number is equivalent as each pixel's pixel sampling steps. "
        "If you set quality steps=2, checkpoint file is created at every timing of each pixel's sample count exceeds "
        "at 2, 4, 6, 8, 10, ... Adaptive sampling case, this steps number is equivalent as internal adaptive sampling "
        "iteration steps. Recommended number is 1~3 range. You can use more than 4 but bigger number always require "
        "longer rendering time. If you set 2, checkpoint file is created after finish every 2 adaptive sampling "
        "iteration execution.");

    sCheckpointTimeCap =
        sceneClass.declareAttribute<Float>("checkpoint_time_cap", Float(0.0f), {"checkpoint time cap"});
    sceneClass.setMetadata(sCheckpointTimeCap, "label", "checkpoint time cap");
    sceneClass.setMetadata(sCheckpointTimeCap,
        SceneClass::sComment,
        "When total render process time exceeds this value, in minutes, the render will finish after the next "
        "checkpoint write. Disabled time cap feature when set to 0.");

    sCheckpointSampleCap = sceneClass.declareAttribute<Int>("checkpoint_sample_cap", Int(0), {"checkpoint sample cap"});
    sceneClass.setMetadata(sCheckpointSampleCap, "label", "checkpoint sample cap");
    sceneClass.setMetadata(sCheckpointSampleCap,
        SceneClass::sComment,
        "When total pixel sample count exceeds this value at every pixel (If you set 1024, each pixel exceeds 1024, "
        "then try to finish), the render will finish after the next checkpoint write. Disabled sample cap feature when "
        "set to 0.");

    sCheckpointOverwrite = sceneClass.declareAttribute<Bool>("checkpoint_overwrite", true, {"checkpoint overwrite"});
    sceneClass.setMetadata(sCheckpointOverwrite, "label", "checkpoint overwrite");
    sceneClass.setMetadata(sCheckpointOverwrite,
        SceneClass::sComment,
        "If true, the last checkpoint file is overwritten when writing out the checkpoint file. If false, the "
        "checkpoint filename is appended with the total number of samples, resulting in the retention of all "
        "checkpoint files.");

    sCheckpointMode = sceneClass.declareAttribute<Int>("checkpoint_mode",
        Int(0),
        rdl2::FLAGS_ENUMERABLE,
        INTERFACE_GENERIC,
        {"checkpoint mode"});
    sceneClass.setMetadata(sCheckpointMode, "label", "checkpoint mode");
    sceneClass.setMetadata(sCheckpointMode,
        SceneClass::sComment,
        "Select whether checkpoint images are written depending on time elapsed or on quality reached.");
    sceneClass.setEnumValue(sCheckpointMode, 0, "time");
    sceneClass.setEnumValue(sCheckpointMode, 1, "quality");

    sCheckpointStartSPP =
        sceneClass.declareAttribute<Int>("checkpoint_start_sample", Int(1), {"checkpoint start sample"});
    sceneClass.setMetadata(sCheckpointStartSPP, "label", "checkpoint start sample");
    sceneClass.setMetadata(sCheckpointStartSPP,
        SceneClass::sComment,
        "Specify samples per pixel (SPP) number. Checkpoint file is created when all pixel's SPP are same or bigger "
        "than this number. Until then, checkpoint file is not created.");

    sCheckpointBgWrite = sceneClass.declareAttribute<Bool>("checkpoint_bg_write", true, {"checkpoint bg write"});
    sceneClass.setMetadata(sCheckpointBgWrite, "label", "checkpoint bg write");
    sceneClass.setMetadata(sCheckpointBgWrite,
        SceneClass::sComment,
        "If true, the checkpoint file write is written in a background thread that runs in parallel with the MCRT "
        "threads. Otherwise, all MCRT threads wait while the checkpoint file is written.");

    sCheckpointPostScript =
        sceneClass.declareAttribute<String>("checkpoint_post_script", "", {"checkpoint post script"});
    sceneClass.setMetadata(sCheckpointPostScript, "label", "checkpoint post script");
    sceneClass.setMetadata(sCheckpointPostScript,
        SceneClass::sComment,
        "This defines the file name of a Lua script executed after every checkpoint file has been written, which is "
        "run in parallel with the ongoing MCRT threads. See further documentation for MoonRay-provided Lua variables "
        "accessible within the script.");

    sCheckpointTotalFiles =
        sceneClass.declareAttribute<Int>("checkpoint_total_files", Int(0), {"checkpoint total files"});
    sceneClass.setMetadata(sCheckpointTotalFiles, "label", "checkpoint total files");
    sceneClass.setMetadata(sCheckpointTotalFiles,
        SceneClass::sComment,
        "Specify total number of checkpoint files for quality based checkpoint mode.This variable is a substitute "
        "parameter of checkpoint_quality_steps.If this value is 0 (= default), the checkpoint generation interval is "
        "controlled by checkpoint_quality_steps variable. If this value is 1 or bigger, checkpoint generation interval "
        "is calculated based on this value and the renderer tries to generate a user defined number of checkpoint "
        "files automatically.This option respects the checkpoint_start_sample variable.In some cases, the renderer "
        "might not create the requested checkpoint_total_files due to current limitation of internal implementation or "
        "user specified bigger than 1 for checkpoint_start_sample variable. However even in that case, the renderer "
        "tries to create the closest number of total checkpoint files which user defined number as "
        "checkpoint_total_files.");

    sCheckpointMaxBgCache =
        sceneClass.declareAttribute<Int>("checkpoint_max_bgcache", Int(2), {"checkpoint max bgcache"});
    sceneClass.setMetadata(sCheckpointMaxBgCache, "label", "checkpoint max bgcache");
    sceneClass.setMetadata(sCheckpointMaxBgCache,
        SceneClass::sComment,
        "Specify the maximum number of queued checkpoint images that the checkpoint-writing background thread can "
        "handle. The value of checkpoint_max_bgcache must be greater than or equal to 1. Once this number is exceeded, "
        "the MCRT threads are suspended while background images are written to create room in the queue. A larger "
        "number can robustly support background writing even with short checkpoint intervals at the expense of memory. "
        "A value of 2 is best for most cases.");

    sCheckpointMaxSnapshotOverhead = sceneClass.declareAttribute<Float>("checkpoint_max_snapshot_overhead",
        Float(0.0f),
        {"checkpoint max snapshot overhead"});
    sceneClass.setMetadata(sCheckpointMaxSnapshotOverhead, "label", "checkpoint max snapshot overhead");
    sceneClass.setMetadata(sCheckpointMaxSnapshotOverhead,
        SceneClass::sComment,
        "Specify max fraction of snapshot overhead threshold for extra snapshot action regarding unexpected "
        "interruption by SIGINT. This value is fraction. If this value is ZERO or negative, no extra snapshot action "
        "is executed and no checkpoint file is generated when SIGINT is received.");

    sCheckpointSnapshotInterval = sceneClass.declareAttribute<Float>("checkpoint_snapshot_interval",
        Float(0.0f),
        {"checkpoint snapshot interval"});
    sceneClass.setMetadata(sCheckpointSnapshotInterval, "label", "checkpoint snapshot interval");
    sceneClass.setMetadata(sCheckpointSnapshotInterval,
        SceneClass::sComment,
        "Interval of time in minutes, about snapshot refreshment regarding interruption by SIGINT. Unit is minute. If "
        "this value is ZERO or negative, checkpoint_max_snapshot_overhead parameter is used instead.");

    // Resume render
    sResumableOutput = sceneClass.declareAttribute<Bool>("resumable_output", false, {"resumable output"});
    sceneClass.setMetadata(sResumableOutput, "label", "resumable output");
    sceneClass.setMetadata(sResumableOutput, SceneClass::sComment, "make aov output as resumable for resume render");

    sResumeRender = sceneClass.declareAttribute<Bool>("resume_render", false, {"resume render"});
    sceneClass.setMetadata(sResumeRender, "label", "resume render");
    sceneClass.setMetadata(sResumeRender, SceneClass::sComment, "resuming render process");

    sOnResumeScript = sceneClass.declareAttribute<String>("on_resume_script", "", {"on resume script"});
    sceneClass.setMetadata(sOnResumeScript, "label", "on resume script");
    sceneClass.setMetadata(sOnResumeScript,
        SceneClass::sComment,
        "Define on-resume lua script name. This script is loaded into the renderer just after renderPrep execution "
        "under resume render mode then executed. This script is not executed if non-resume render mode even if you set "
        "script name.Renderer sets some lua global variables and lua script can access them. We can get resume render "
        "start condition (true=properly started or false=failed to start as resume render and fall back to normal "
        "rendering) via lua global variable. See details in rendering-wiki checkpoint/resume page. If empty, on-resume "
        "script execution is disabled.");

    // Global overriding toggles
    sEnableMotionBlur = sceneClass.declareAttribute<Bool>("enable_motion_blur", true, {"enable motion blur"});
    sceneClass.setMetadata(sEnableMotionBlur, "label", "enable motion blur");

    sEnableDof = sceneClass.declareAttribute<Bool>("enable_dof", true, {"enable DOF"});
    sceneClass.setMetadata(sEnableDof, "label", "enable DOF");

    sEnableMaxGeomResolution =
        sceneClass.declareAttribute<Bool>("enable_max_geometry_resolution", false, {"enable max geometry resolution"});
    sceneClass.setMetadata(sEnableMaxGeomResolution, "label", "enable max geometry resolution");

    sMaxGeomResolution =
        sceneClass.declareAttribute<Int>("max_geometry_resolution", Int(INT_MAX), {"max geometry resolution"});
    sceneClass.setMetadata(sMaxGeomResolution, "label", "max geometry resolution");

    sEnableDisplacement = sceneClass.declareAttribute<Bool>("enable_displacement", true, {"enable displacement"});
    sceneClass.setMetadata(sEnableDisplacement, "label", "enable displacement");

    sEnableSSS =
        sceneClass.declareAttribute<Bool>("enable_subsurface_scattering", true, {"enable subsurface scattering"});
    sceneClass.setMetadata(sEnableSSS, "label", "enable subsurface scattering");

    sEnableShadowing = sceneClass.declareAttribute<Bool>("enable_shadowing", true, {"enable shadowing"});
    sceneClass.setMetadata(sEnableShadowing, "label", "enable shadowing");

    sEnablePresenceShadows =
        sceneClass.declareAttribute<Bool>("enable_presence_shadows", false, {"enable presence shadows"});
    sceneClass.setMetadata(sEnablePresenceShadows, "label", "enable presence shadows");

    sLightsVisibleInCameraKey =
        sceneClass.declareAttribute<Bool>("lights_visible_in_camera", false, {"lights visible in camera"});
    sceneClass.setMetadata(sLightsVisibleInCameraKey, "label", "lights visible in camera");

    sPropagateVisibilityBounceType = sceneClass.declareAttribute<Bool>("propagate_visibility_bounce_type",
        false,
        {"propagate visibility bounce type"});
    sceneClass.setMetadata(sPropagateVisibilityBounceType, "label", "propagate visibility bounce type");
    sceneClass.setMetadata(sPropagateVisibilityBounceType,
        SceneClass::sComment,
        "turns on/off propagation for ray visibility masks");

    sShadowTerminatorFix = sceneClass.declareAttribute<Int>("shadow_terminator_fix",
        Int(ShadowTerminatorFix::OFF),
        rdl2::FLAGS_ENUMERABLE);
    sceneClass.setEnumValue(sShadowTerminatorFix, Int(ShadowTerminatorFix::OFF), "Off");
    sceneClass.setEnumValue(sShadowTerminatorFix, Int(ShadowTerminatorFix::CUSTOM), "On");
    sceneClass.setEnumValue(sShadowTerminatorFix,
        Int(ShadowTerminatorFix::SINE_COMPENSATION),
        "On (Sine Compensation Alternative)");
    sceneClass.setEnumValue(sShadowTerminatorFix, Int(ShadowTerminatorFix::GGX), "On (GGX Compensation Alternative)");
    sceneClass.setEnumValue(sShadowTerminatorFix,
        Int(ShadowTerminatorFix::COSINE_COMPENSATION),
        "On (Cosine Compensation Alternative");
    sceneClass.setMetadata(sShadowTerminatorFix, "label", "shadow terminator fix");
    sceneClass.setMetadata(sShadowTerminatorFix,
        SceneClass::sComment,
        "Attempt to soften hard shadow terminator boundaries due to shading/geometric normal deviations.  \"ON uses a "
        "custom terminator softening method. Cosine Compensation\" is Chiang's 2019 SIGGRAPH technique.  \"GGX\" is "
        "Estevez's raytracing gems technique.  \"Sine Compensation\" is a sine based modification of Chiang's method. "
        "Different scenes may work better with different techniques.  The recommendation is to start with the custom "
        "compensation ON, then sine compensation technique, then GGX, then cosine.");

    sThreads = sceneClass.declareAttribute<Int>("threads", Int(0));

    sMachineId = sceneClass.declareAttribute<Int>("machine_id", -1, {"machine id"});
    sceneClass.setMetadata(sMachineId, "label", "machine id");

    sNumMachines = sceneClass.declareAttribute<Int>("num_machines", -1, {"num machines"});
    sceneClass.setMetadata(sNumMachines, "label", "num machines");

    sTaskDistributionType = sceneClass.declareAttribute<Int>("task_distribution_type", Int(1), rdl2::FLAGS_ENUMERABLE);
    sceneClass.setMetadata(sTaskDistributionType, "label", "task distribution type");
    sceneClass.setEnumValue(sTaskDistributionType,
        (int)TaskDistributionType::NON_OVERLAPPED_TILE,
        "non-overlapped tile");
    sceneClass.setEnumValue(sTaskDistributionType, (int)TaskDistributionType::MULTIPLEX_PIXEL, "multiplex pixel");

    sInteractiveKey = sceneClass.declareAttribute<Bool>("interactive_mode", false, {"interactive mode"});
    sceneClass.setMetadata(sInteractiveKey, "label", "interactive mode");

    sProgressiveKey = sceneClass.declareAttribute<Bool>("progressive_shading", false, {"progressive shading"});
    sceneClass.setMetadata(sProgressiveKey, "label", "progressive shading");

    sBatchTileOrder = sceneClass.declareAttribute<Int>("batch_tile_order",
        Int(4),
        rdl2::FLAGS_ENUMERABLE,
        INTERFACE_GENERIC,
        {"batch tile order"});
    sceneClass.setMetadata(sBatchTileOrder, "label", "batch tile order");
    sceneClass.setEnumValue(sBatchTileOrder, 0, "top");
    sceneClass.setEnumValue(sBatchTileOrder, 1, "bottom");
    sceneClass.setEnumValue(sBatchTileOrder, 2, "left");
    sceneClass.setEnumValue(sBatchTileOrder, 3, "right");
    sceneClass.setEnumValue(sBatchTileOrder, 4, "morton");
    sceneClass.setEnumValue(sBatchTileOrder, 5, "random");
    sceneClass.setEnumValue(sBatchTileOrder, 6, "spiral square");
    sceneClass.setEnumValue(sBatchTileOrder, 7, "spiral rect");

    sProgressiveTileOrder = sceneClass.declareAttribute<Int>("progressive_tile_order",
        Int(4),
        rdl2::FLAGS_ENUMERABLE,
        INTERFACE_GENERIC,
        {"progressive tile order"});
    sceneClass.setMetadata(sProgressiveTileOrder, "label", "progressive tile order");
    sceneClass.setEnumValue(sProgressiveTileOrder, 0, "top");
    sceneClass.setEnumValue(sProgressiveTileOrder, 1, "bottom");
    sceneClass.setEnumValue(sProgressiveTileOrder, 2, "left");
    sceneClass.setEnumValue(sProgressiveTileOrder, 3, "right");
    sceneClass.setEnumValue(sProgressiveTileOrder, 4, "morton");
    sceneClass.setEnumValue(sProgressiveTileOrder, 5, "random");
    sceneClass.setEnumValue(sProgressiveTileOrder, 6, "spiral square");
    sceneClass.setEnumValue(sProgressiveTileOrder, 7, "spiral rect");

    sCheckpointTileOrder = sceneClass.declareAttribute<Int>("checkpoint_tile_order",
        Int(4),
        rdl2::FLAGS_ENUMERABLE,
        INTERFACE_GENERIC,
        {"checkpoint tile order"});
    sceneClass.setMetadata(sCheckpointTileOrder, "label", "checkpoint tile order");
    sceneClass.setEnumValue(sCheckpointTileOrder, 0, "top");
    sceneClass.setEnumValue(sCheckpointTileOrder, 1, "bottom");
    sceneClass.setEnumValue(sCheckpointTileOrder, 2, "left");
    sceneClass.setEnumValue(sCheckpointTileOrder, 3, "right");
    sceneClass.setEnumValue(sCheckpointTileOrder, 4, "morton");
    sceneClass.setEnumValue(sCheckpointTileOrder, 5, "random");
    sceneClass.setEnumValue(sCheckpointTileOrder, 6, "spiral square");
    sceneClass.setEnumValue(sCheckpointTileOrder, 7, "spiral rect");

    sOutputFile = sceneClass.declareAttribute<String>("output_file", "scene.exr", {"output file"});
    sceneClass.setMetadata(sOutputFile, "label", "output file");
    sceneClass.setMetadata(sOutputFile,
        SceneClass::sComment,
        "This specifies the output path for the beauty image (RGBA). This is independent of the AOV RenderOutputs, "
        "which can also write a beauty image.");

    sTemporaryDirectory = sceneClass.declareAttribute<String>("tmp_dir", "", {"tmp dir"});
    sceneClass.setMetadata(sTemporaryDirectory, "label", "tmp dir");
    sceneClass.setMetadata(sTemporaryDirectory,
        SceneClass::sComment,
        "Define temporary directory name for temporary file generation. Use $TMPDIR environment variable value if this "
        "variable is empty.If $TMPDIR is also empty, use /tmp");

    sTwoStageOutput = sceneClass.declareAttribute<Bool>("two_stage_output", true, {"two stage output"});
    sceneClass.setMetadata(sTwoStageOutput, "label", "two stage output");
    sceneClass.setMetadata(sTwoStageOutput,
        SceneClass::sComment,
        "Selection of image file write uses two stage output logic or not. Two stage output (=true: default) is that "
        "the image file is written out to temporary file location first and copy/rename next. This solution greatly "
        "reduces the risk of output data collapsing from unexpected render process termination for both of final "
        "output and checkpoint output. Temporary file directory is defined by tmp_dir scene_variable.");

    sDebugKey = sceneClass.declareAttribute<Bool>("debug", false);

    sInfoKey = sceneClass.declareAttribute<Bool>("info", false);

    sWarningKey = sceneClass.declareAttribute<Bool>("warning", true);

    sErrorKey = sceneClass.declareAttribute<Bool>("error", true);

    sFatalColor = sceneClass.declareAttribute<Rgb>("fatal_color", Rgb(1.0f, 0.0f, 1.0f), {"fatal color"});
    sceneClass.setMetadata(sFatalColor, "label", "fatal color");

    sStatsFile = sceneClass.declareAttribute<String>("stats_file", "", {"stats file"});
    sceneClass.setMetadata(sStatsFile, "label", "stats file");

    sAthenaDebug = sceneClass.declareAttribute<Bool>("athena_debug", false, {"athena debug"});
    sceneClass.setMetadata(sAthenaDebug, "label", "athena debug");

    // "debug pixel" is defined such that a coordinate of (0, 0) maps to the left,
    // bottom of the region window (i.e. the render buffer).
    IntVector debugPixel = {minIntVal, minIntVal};
    sDebugPixel          = sceneClass.declareAttribute<IntVector>("debug_pixel", debugPixel, {"debug pixel"});
    sceneClass.setMetadata(sDebugPixel, "label", "debug pixel");

    sDebugRaysFile = sceneClass.declareAttribute<String>("debug_rays_file", "", {"debug rays file"});
    sceneClass.setMetadata(sDebugRaysFile, "label", "debug rays file");

    IntVector debugRaysRange = {minIntVal, minIntVal};
    sDebugRaysPrimaryRange   = sceneClass.declareAttribute<IntVector>("debug_rays_primary_range",
        debugRaysRange,
        {"debug rays primary range"});
    sceneClass.setMetadata(sDebugRaysPrimaryRange, "label", "debug rays primary range");

    IntVector debugRaysDepthRange = {minIntVal, minIntVal};
    sDebugRaysDepthRange          = sceneClass.declareAttribute<IntVector>("debug_rays_depth_range",
        debugRaysDepthRange,
        {"debug rays depth range"});
    sceneClass.setMetadata(sDebugRaysDepthRange, "label", "debug rays depth range");

    // Debug console
    sDebugConsole = sceneClass.declareAttribute<Int>("debug_console", Int(-1), {"debug console"});
    sceneClass.setMetadata(sDebugConsole, "label", "debug console");
    sceneClass.setMetadata(sDebugConsole,
        SceneClass::sComment,
        "Specify port number for debug console. If you set -1 (=default), all debug console functionalities are "
        "disabled. If you set 0 or positive port number, debug console functionalities are enabled. If enabled, we can "
        "send commands via telnet connection and control rendering behavior for debugging purposes. If you set 0, the "
        "kernel finds the available port for you and displays the port number to the cerr. Otherwise you have to set "
        "the available port number yourself.");

    sValidateGeometry = sceneClass.declareAttribute<Bool>("validate_geometry", false, {"validate geometry"});
    sceneClass.setMetadata(sValidateGeometry, "label", "validate geometry");
    sceneClass.setMetadata(sValidateGeometry, SceneClass::sComment, "Checks geometry for bad data");

    // Grouping the attributes for Torch - the order of
    // the attributes should be the same as how they are defined.
    sceneClass.setGroup("Frame", sMinFrameKey);
    sceneClass.setGroup("Frame", sMaxFrameKey);
    sceneClass.setGroup("Frame", sFrameKey);

    sceneClass.setGroup("Camera and Layer", sCamera);
    sceneClass.setGroup("Camera and Layer", sDicingCamera);
    sceneClass.setGroup("Camera and Layer", sLayer);
    sceneClass.setGroup("Metadata", sAttrExrHeaderAttributes);

    sceneClass.setGroup("Image Size", sImageWidth);
    sceneClass.setGroup("Image Size", sImageHeight);
    sceneClass.setGroup("Image Size", sResKey);
    sceneClass.setGroup("Image Size", sApertureWindow);
    sceneClass.setGroup("Image Size", sRegionWindow);
    sceneClass.setGroup("Image Size", sSubViewport);

    sceneClass.setGroup("Motion and Scale", sMotionSteps);
    sceneClass.setGroup("Motion and Scale", sSceneScaleKey);

    sceneClass.setGroup("Sampling", sPixelSamplesSqrt);
    sceneClass.setGroup("Sampling", sLightSamplesSqrt);
    sceneClass.setGroup("Sampling", sBsdfSamplesSqrt);
    sceneClass.setGroup("Sampling", sBsdfSamplerStrategy);
    sceneClass.setGroup("Sampling", sBssrdfSamplesSqrt);
    sceneClass.setGroup("Sampling", sMaxDepth);
    sceneClass.setGroup("Sampling", sMaxDiffuseDepth);
    sceneClass.setGroup("Sampling", sMaxGlossyDepth);
    sceneClass.setGroup("Sampling", sMaxMirrorDepth);
    sceneClass.setGroup("Sampling", sMaxPresenceDepth);
    sceneClass.setGroup("Sampling", sMaxHairDepth);
    sceneClass.setGroup("Sampling", sDisableOptimizedHairSampling);
    sceneClass.setGroup("Sampling", sMaxSubsurfacePerPath);
    sceneClass.setGroup("Sampling", sRussianRouletteThreshold);
    sceneClass.setGroup("Sampling", sTransparencyThreshold);
    sceneClass.setGroup("Sampling", sPresenceThreshold);
    sceneClass.setGroup("Sampling", sLockFrameNoise);

    sceneClass.setGroup("Volumes", sMaxVolumeDepth);
    sceneClass.setGroup("Volumes", sVolumeQuality);
    sceneClass.setGroup("Volumes", sVolumeShadowQuality);
    sceneClass.setGroup("Volumes", sVolumeIlluminationSamples);
    sceneClass.setGroup("Volumes", sVolumeOpacityThreshold);
    sceneClass.setGroup("Volumes", sVolumeOverlapMode);
    sceneClass.setGroup("Volumes", sVolumeAttenuationFactor);
    sceneClass.setGroup("Volumes", sVolumeContributionFactor);
    sceneClass.setGroup("Volumes", sVolumePhaseAttenuationFactor);

    sceneClass.setGroup("Path Guide", sPathGuideEnable);

    sceneClass.setGroup("Fireflies Removal", sSampleClampingValue);
    sceneClass.setGroup("Fireflies Removal", sSampleClampingDepth);
    sceneClass.setGroup("Fireflies Removal", sRoughnessClampingFactor);

    sceneClass.setGroup("Filtering", sTextureBlur);
    sceneClass.setGroup("Filtering", sPixelFilterWidth);
    sceneClass.setGroup("Filtering", sPixelFilterType);

    sceneClass.setGroup("Deep Images", sDeepFormat);
    sceneClass.setGroup("Deep Images", sDeepCurvatureTolerance);
    sceneClass.setGroup("Deep Images", sDeepZTolerance);
    sceneClass.setGroup("Deep Images", sDeepVolCompressionRes);
    sceneClass.setGroup("Deep Images", sDeepIDAttributeNames);
    sceneClass.setGroup("Deep Images", sDeepMaxLayers);
    sceneClass.setGroup("Deep Images", sDeepLayerBias);

    sceneClass.setGroup("Caching", sTextureCacheSizeMb);
    sceneClass.setGroup("Caching", sTextureFileHandleCount);
    sceneClass.setGroup("Caching", sFastGeomUpdate);

    sceneClass.setGroup("Checkpoint", sCheckpointActive);
    sceneClass.setGroup("Checkpoint", sCheckpointInterval);
    sceneClass.setGroup("Checkpoint", sCheckpointQualitySteps);
    sceneClass.setGroup("Checkpoint", sCheckpointTimeCap);
    sceneClass.setGroup("Checkpoint", sCheckpointSampleCap);
    sceneClass.setGroup("Checkpoint", sCheckpointOverwrite);
    sceneClass.setGroup("Checkpoint", sCheckpointMode);
    sceneClass.setGroup("Checkpoint", sCheckpointStartSPP);
    sceneClass.setGroup("Checkpoint", sCheckpointBgWrite);
    sceneClass.setGroup("Checkpoint", sCheckpointPostScript);
    sceneClass.setGroup("Checkpoint", sCheckpointTotalFiles);
    sceneClass.setGroup("Checkpoint", sCheckpointMaxBgCache);
    sceneClass.setGroup("Checkpoint", sCheckpointMaxSnapshotOverhead);
    sceneClass.setGroup("Checkpoint", sCheckpointSnapshotInterval);

    sceneClass.setGroup("Resume Render", sResumableOutput);
    sceneClass.setGroup("Resume Render", sResumeRender);
    sceneClass.setGroup("Resume Render", sOnResumeScript);

    sceneClass.setGroup("Global Toggles", sEnableMotionBlur);
    sceneClass.setGroup("Global Toggles", sEnableDof);
    sceneClass.setGroup("Global Toggles", sEnableMaxGeomResolution);
    sceneClass.setGroup("Global Toggles", sMaxGeomResolution);
    sceneClass.setGroup("Global Toggles", sEnableDisplacement);
    sceneClass.setGroup("Global Toggles", sEnableSSS);
    sceneClass.setGroup("Global Toggles", sEnableShadowing);
    sceneClass.setGroup("Global Toggles", sEnablePresenceShadows);
    sceneClass.setGroup("Global Toggles", sLightsVisibleInCameraKey);
    sceneClass.setGroup("Global Toggles", sPropagateVisibilityBounceType);
    sceneClass.setGroup("Global Toggles", sShadowTerminatorFix);

    sceneClass.setGroup("Driver", sThreads);
    sceneClass.setGroup("Driver", sMachineId);
    sceneClass.setGroup("Driver", sNumMachines);
    sceneClass.setGroup("Driver", sTaskDistributionType);
    sceneClass.setGroup("Driver", sInteractiveKey);
    sceneClass.setGroup("Driver", sProgressiveKey);
    sceneClass.setGroup("Driver", sOutputFile);
    sceneClass.setGroup("Driver", sTemporaryDirectory);

    sceneClass.setGroup("Logging", sDebugKey);
    sceneClass.setGroup("Logging", sInfoKey);
    sceneClass.setGroup("Logging", sWarningKey);
    sceneClass.setGroup("Logging", sErrorKey);
    sceneClass.setGroup("Logging", sFatalColor);
    sceneClass.setGroup("Logging", sStatsFile);
    sceneClass.setGroup("Logging", sAthenaDebug);

    sceneClass.setGroup("Debug", sDebugPixel);
    sceneClass.setGroup("Debug", sDebugRaysFile);
    sceneClass.setGroup("Debug", sDebugRaysPrimaryRange);
    sceneClass.setGroup("Debug", sDebugRaysDepthRange);
    sceneClass.setGroup("Debug", sDebugConsole);
    sceneClass.setGroup("Debug", sValidateGeometry);

    return interface;
}

uint32_t
SceneVariables::getRezedWidth() const
{
    return static_cast<uint32_t>(getRezedRegionWindow().width());
}

uint32_t
SceneVariables::getRezedHeight() const
{
    return static_cast<uint32_t>(getRezedRegionWindow().height());
}

HalfOpenViewport SceneVariables::getRezedApertureWindow() const
{
    float invRes = 1.f / get(sResKey);

    const std::vector<int>& window = get(sApertureWindow);
    if (window[0] == std::numeric_limits<int>::lowest()) {
        // Assume the sApertureWindow hasn't been set and key off of the
        // sWidth and sHeigh attributes instead.
        int width       = get(sImageWidth);
        int height      = get(sImageHeight);
        int rezedWidth  = math::max(int(float(width) * invRes), 1);
        int rezedHeight = math::max(int(float(height) * invRes), 1);
        return HalfOpenViewport(0, 0, rezedWidth, rezedHeight);
    }

    return HalfOpenViewport(window, invRes);
}

HalfOpenViewport SceneVariables::getRezedRegionWindow() const
{
    const std::vector<int>& window = get(sRegionWindow);
    if (window[0] == std::numeric_limits<int>::lowest()) {
        // Assume the sRegionWindow and replace it with the aperture window instead.
        return getRezedApertureWindow();
    }

    float invRes = 1.f / get(sResKey);

    return HalfOpenViewport(window, invRes);
}

HalfOpenViewport SceneVariables::getRezedSubViewport() const
{
    HalfOpenViewport regionViewport = getRezedRegionWindow();

    HalfOpenViewport screen(0, 0, regionViewport.width(), regionViewport.height());

    math::Vec2i debugPixel;
    if (getDebugPixel(debugPixel)) {
        if (screen.contains(debugPixel.x, debugPixel.y)) {
            return HalfOpenViewport(debugPixel.x, debugPixel.y, debugPixel.x + 1, debugPixel.y + 1);
        }
    }

    const std::vector<int>& viewport = get(sSubViewport);
    if (viewport[0] == std::numeric_limits<int>::lowest()) {
        return screen;
    }

    // Clip rezed sub-viewport to eventual screen window.
    float invRes = 1.f / get(sResKey);
    int   minX   = int(float(viewport[0]) * invRes);
    int   minY   = int(float(viewport[1]) * invRes);
    int   maxX   = int(float(viewport[2]) * invRes);
    int   maxY   = int(float(viewport[3]) * invRes);

    minX = math::max(minX, screen.mMinX);
    minY = math::max(minY, screen.mMinY);
    maxX = math::min(maxX, screen.mMaxX);
    maxY = math::min(maxY, screen.mMaxY);

    MNRY_ASSERT(minX >= 0);
    MNRY_ASSERT(minY >= 0);

    return HalfOpenViewport(minX, minY, maxX, maxY);
}

int
SceneVariables::getMachineId() const
{
    int machineId = get(sMachineId);

    if (machineId >= 0) {
        return machineId;
    }

    // Not set, single machine only.
    return 0;
}

int
SceneVariables::getNumMachines() const
{
    int numMachines = get(sNumMachines);

    if (numMachines > 1) {
        return numMachines ;
    }

    // Not set, single machine only.
    return 1;
}

SceneObject*
SceneVariables::getLayer() const
{
    auto layerSceneObj = get(sLayer);
    if (layerSceneObj) {
        return layerSceneObj;
    }

    // Grab the first layer we find
    const SceneContext* sceneContext = getSceneClass().getSceneContext();
    for (auto iter = sceneContext->beginSceneObject(); iter != sceneContext->endSceneObject(); ++iter) {
        rdl2::SceneObject* obj = iter->second;
        if (obj->isA<rdl2::Layer>()) {
            return obj;
        }
    }

    // Couldn't find a layer
    return NULL;
}

const SceneObject*
SceneVariables::getExrHeaderAttributes() const
{
    auto metadataSceneObj = get(sAttrExrHeaderAttributes);
    if (metadataSceneObj) {
        return metadataSceneObj;
    }

    return NULL;
}

bool
SceneVariables::getDebugPixel(math::Vec2i &pixel) const
{
    const std::vector<int>& debugPixel = get(sDebugPixel);
    if (debugPixel[0] == std::numeric_limits<int>::lowest()) { // unset
        return false;
    } else {
        pixel.x = debugPixel[0];
        pixel.y = debugPixel[1];
    }

    return true;
}

bool
SceneVariables::getDebugRaysPrimaryRange(int &start, int &end) const
{
    const std::vector<int>& raysRange = get(sDebugRaysPrimaryRange);
    if (raysRange[0] == std::numeric_limits<int>::lowest()) { // unset
        return false;
    } else {
        start = raysRange[0];
        end   = raysRange[1];
    }

    return true;
}

bool
SceneVariables::getDebugRaysDepthRange(int &start, int &end) const
{
    const std::vector<int>& raysDepthRange = get(sDebugRaysDepthRange);
    if (raysDepthRange[0] == std::numeric_limits<int>::lowest()) { // unset
        return false;
    } else {
        start = raysDepthRange[0];
        end   = raysDepthRange[1];
    }

    return true;
}

bool
SceneVariables::getSubViewport(math::HalfOpenViewport& viewport) const
{
    const std::vector<int>& viewportVector = get(sSubViewport);
    if (viewportVector[0] == std::numeric_limits<int>::lowest()) { // unset
        return false;
    } else {
        viewport.mMinX = viewportVector[0];
        viewport.mMinY = viewportVector[1];
        viewport.mMaxX = viewportVector[2];
        viewport.mMaxY = viewportVector[3];
    }

    return true;
}

void
SceneVariables::disableSubViewport()
{
    constexpr int minIntVal = std::numeric_limits<int>::lowest();

    std::vector<int> viewportVector = {minIntVal, minIntVal, minIntVal, minIntVal};
    UpdateGuard guard(this);
    set(sSubViewport, viewportVector);
}

std::string
SceneVariables::getTmpDir() const
{
    std::string tmpDir = get(sTemporaryDirectory);
    if (tmpDir.empty()) {
        tmpDir = util::getenv<std::string>("TMPDIR");
    }
    if (tmpDir.back() == '/') tmpDir.pop_back();
    if (tmpDir.empty()) tmpDir = "/tmp";
    return tmpDir;
}

} // namespace rdl2
} // namespace scene_rdl2

