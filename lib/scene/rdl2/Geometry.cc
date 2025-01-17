// Copyright 2023 DreamWorks Animation LLC
// SPDX-License-Identifier: Apache-2.0


#include "Geometry.h"

#include "SceneClass.h"
#include "Types.h"
#include "VisibilityFlags.h"

#include <string>

namespace scene_rdl2 {
namespace rdl2 {

AttributeKey<String> Geometry::sLabel;
AttributeKey<SceneObjectVector> Geometry::sReferenceGeometries;
AttributeKey<Bool> Geometry::sStaticKey;
AttributeKey<Int> Geometry::sSideTypeKey;
AttributeKey<Bool> Geometry::sReverseNormals;
AttributeKey<Bool> Geometry::sVisibleCamera;
AttributeKey<Bool> Geometry::sVisibleShadow;
AttributeKey<Bool> Geometry::sVisibleDiffuseReflection;
AttributeKey<Bool> Geometry::sVisibleDiffuseTransmission;
AttributeKey<Bool> Geometry::sVisibleGlossyReflection;
AttributeKey<Bool> Geometry::sVisibleGlossyTransmission;
AttributeKey<Bool> Geometry::sVisibleMirrorReflection;
AttributeKey<Bool> Geometry::sVisibleMirrorTransmission;
AttributeKey<Bool> Geometry::sVisiblePhase;
AttributeKey<Float> Geometry::sRayEpsilon;
AttributeKey<Float> Geometry::sShadowRayEpsilon;
AttributeKey<String> Geometry::sShadowReceiverLabel;
AttributeKey<String> Geometry::sShadowExclusionMappings;
AttributeKey<Bool> Geometry::sContainsCamera;
AttributeKey<SceneObject*> Geometry::sDicingCamera;

Geometry::Geometry(const SceneClass& sceneClass, const std::string& name) :
    Parent(sceneClass, name),
    mProcedural(nullptr),
    mRender2Object(math::one)
{
    // Add the Geometry interface.
    mType |= INTERFACE_GEOMETRY;
}

Geometry::~Geometry()
{
}

SceneObjectInterface
Geometry::declare(SceneClass& sceneClass)
{
    auto interface = Parent::declare(sceneClass);

    sLabel = sceneClass.declareAttribute<String>("label", "");
    sceneClass.setMetadata(sLabel, SceneClass::sComment, "label used in material aov expresssions");

    sReferenceGeometries = sceneClass.declareAttribute<SceneObjectVector>(
        "references", SceneObjectVector(),
        FLAGS_NONE, INTERFACE_GEOMETRY);
    sceneClass.setMetadata(sReferenceGeometries, SceneClass::sComment,
        "list of geometries that geometry procedural can reference "
        "during procedural generate/update stages. "
        "For example, an instancer geometry procedural can instance "
        "primitives generated by the reference geometry procedural.");

    sStaticKey = sceneClass.declareAttribute<Bool>("static", true);
    sceneClass.setMetadata(sStaticKey, SceneClass::sComment,
        "disable if the geometry will be updated between frames");

    sSideTypeKey = sceneClass.declareAttribute<Int>("side_type", TWO_SIDED, FLAGS_ENUMERABLE, INTERFACE_GENERIC, { "side type" });
    sceneClass.setMetadata(sSideTypeKey, "label", "side type");
    sceneClass.setEnumValue(sSideTypeKey, TWO_SIDED, "force two-sided");
    sceneClass.setEnumValue(sSideTypeKey, SINGLE_SIDED, "force single-sided");
    sceneClass.setEnumValue(sSideTypeKey, MESH_DEFAULT_SIDED, "use mesh sidedness");
    sceneClass.setMetadata(sSideTypeKey, SceneClass::sComment,
        "set single sidedness of the mesh, will affect the visibility of the mesh based on normal direction");

    sReverseNormals = sceneClass.declareAttribute<Bool>("reverse_normals", false, { "reverse normals" });
    sceneClass.setMetadata(sReverseNormals, "label", "reverse normals");
    sceneClass.setMetadata(sReverseNormals, "comment",
        "enable to reverse the normals in the geometry");

    sVisibleCamera = sceneClass.declareAttribute<Bool>("visible_in_camera", true, { "visible in camera" });
    sceneClass.setMetadata(sVisibleCamera, "label", "visible in camera");
    sceneClass.setMetadata(sVisibleCamera, SceneClass::sComment,
        "whether the geometry is visible to camera rays");

    sVisibleShadow = sceneClass.declareAttribute<Bool>("visible_shadow", true, { "visible shadow" });
    sceneClass.setMetadata(sVisibleShadow, "label", "visible shadow");
    sceneClass.setMetadata(sVisibleShadow, SceneClass::sComment,
        "whether the geometry casts shadows");

    sVisibleDiffuseReflection = sceneClass.declareAttribute<Bool>("visible_diffuse_reflection", true, { "visible diffuse reflection" });
    sceneClass.setMetadata(sVisibleDiffuseReflection, "label", "visible diffuse reflection");
    sceneClass.setMetadata(sVisibleDiffuseReflection, SceneClass::sComment,
        "whether the geometry is visible in diffuse reflection");

    sVisibleDiffuseTransmission = sceneClass.declareAttribute<Bool>("visible_diffuse_transmission", true, { "visible diffuse transmission" });
    sceneClass.setMetadata(sVisibleDiffuseTransmission, "label", "visible diffuse transmission");
    sceneClass.setMetadata(sVisibleDiffuseTransmission, SceneClass::sComment,
        "whether the geometry is visible in diffuse transmission");

    sVisibleGlossyReflection = sceneClass.declareAttribute<Bool>("visible_glossy_reflection", true, { "visible glossy reflection" });
    sceneClass.setMetadata(sVisibleGlossyReflection, "label", "visible glossy reflection");
    sceneClass.setMetadata(sVisibleGlossyReflection, SceneClass::sComment,
        "whether the geometry is visible in glossy reflection.");

    sVisibleGlossyTransmission = sceneClass.declareAttribute<Bool>("visible_glossy_transmission", true, { "visible glossy transmission" });
    sceneClass.setMetadata(sVisibleGlossyTransmission, "label", "visible glossy transmission");
    sceneClass.setMetadata(sVisibleGlossyTransmission, SceneClass::sComment,
        "whether the geometry is visible in glossy transmission (refraction).");

    sVisibleMirrorReflection = sceneClass.declareAttribute<Bool>("visible_mirror_reflection", true, { "visible mirror reflection" });
    sceneClass.setMetadata(sVisibleMirrorReflection, "label", "visible mirror reflection");
    sceneClass.setMetadata(sVisibleMirrorReflection, SceneClass::sComment,
        "whether the geometry is visible in miror reflection.");

    sVisibleMirrorTransmission = sceneClass.declareAttribute<Bool>("visible_mirror_transmission", true, { "visible mirror transmission" });
    sceneClass.setMetadata(sVisibleMirrorTransmission, "label", "visible mirror transmission");
    sceneClass.setMetadata(sVisibleMirrorTransmission, SceneClass::sComment,
        "whether the geometry is visible in miror transmission (refraction).");

    sVisiblePhase = sceneClass.declareAttribute<Bool>("visible_volume", true, { "visible volume" });
    sceneClass.setMetadata(sVisiblePhase, "label", "visible volume");
    sceneClass.setMetadata(sVisiblePhase, "comment",
        "whether the geometry is visible in indirect volume rays");

    sRayEpsilon = sceneClass.declareAttribute<Float>("ray_epsilon", Float(0.0f),
        FLAGS_CAN_SKIP_GEOM_RELOAD, INTERFACE_GENERIC, {"ray epsilon"});
    sceneClass.setMetadata(sRayEpsilon, "label", "ray epsilon");
    sceneClass.setMetadata(sRayEpsilon, "comment",
        "When a secondary ray is fired, anything within this distance of the "
        "intersection point will be ignored.  Instead, it is considered part of "
        "the current intersection's geometry.  If zero, an automatically calculated "
        "epsilon will be used.");

    sShadowRayEpsilon = sceneClass.declareAttribute<Float>("shadow_ray_epsilon", Float(0.0f),
        FLAGS_CAN_SKIP_GEOM_RELOAD, INTERFACE_GENERIC);
    sceneClass.setMetadata(sShadowRayEpsilon, "label", "shadow ray epsilon");
    sceneClass.setMetadata(sShadowRayEpsilon, "comment",
        "When a shadow ray is fired, anything within this distance of the "
        "intersection point will be ignored.  If this value is less than \"ray_epsilon\", "
        "then it has no additional effect.");

    sShadowReceiverLabel = sceneClass.declareAttribute<String>("shadow_receiver_label", "", {"shadow receiver label"});
    sceneClass.setMetadata(sShadowReceiverLabel, SceneClass::sComment,
        "Label used to associate Geometry objects into sets. Then, using the "
        "[\"shadow_exclusion_mappings\"] attribute, shadows from specified geometry "
        "parts can be suppressed from casting onto specified sets.");

    sShadowExclusionMappings = sceneClass.declareAttribute<String>("shadow_exclusion_mappings", "",
                                                                   {"shadow exclusion mappings"});
    sceneClass.setMetadata(sShadowExclusionMappings, SceneClass::sComment,
        "List of mappings of the form A:B where:\n"
        "A is a list of names of parts to be mapped, or asterisk to map the whole geometry\n"
        "B is a list of labels corresponding to the sets corresponding to distinct values of "
        "[\"shadow_receiver_label\"], or asterisk to map to all such sets.");

    sContainsCamera = sceneClass.declareAttribute<Bool>("contains_camera", false);
    sceneClass.setMetadata(sContainsCamera, SceneClass::sComment,
        "Specifies whether the geometry contains the camera and should be used for IOR tracking. This should not be "
        "changed by the user -- they should instead attach the relevant geometry to the camera, which will then flag "
        "this geometry.");

    sDicingCamera = sceneClass.declareAttribute<SceneObject*>("dicing_camera", nullptr);

    return interface | INTERFACE_GEOMETRY;
}

int
Geometry::getVisibilityMask() const
{
    int visibilityMask = NONE_VISIBLE;
    visibilityMask |= get(sVisibleCamera) ? CAMERA : 0;
    visibilityMask |= get(sVisibleShadow) ? SHADOW : 0;
    visibilityMask |= get(sVisibleDiffuseReflection) ? DIFFUSE_REFLECTION : 0;
    visibilityMask |= get(sVisibleDiffuseTransmission) ? DIFFUSE_TRANSMISSION : 0;
    visibilityMask |= get(sVisibleGlossyReflection) ? GLOSSY_REFLECTION : 0;
    visibilityMask |= get(sVisibleGlossyTransmission) ? GLOSSY_TRANSMISSION : 0;
    visibilityMask |= get(sVisibleMirrorReflection) ? MIRROR_REFLECTION : 0;
    visibilityMask |= get(sVisibleMirrorTransmission) ? MIRROR_TRANSMISSION : 0;
    visibilityMask |= get(sVisiblePhase) ? PHASE_REFLECTION | PHASE_TRANSMISSION: 0;
    visibilityMask |= get(sContainsCamera) ? CONTAINS_CAMERA : 0;
    return visibilityMask;
}

bool
Geometry::requiresGeometryUpdate(UpdateHelper& sceneObjects, int depth)
{
    for (auto it = mSceneClass.beginAttributes();
        it != mSceneClass.endAttributes(); ++it) {
        const Attribute* attribute = *it;
        // some attributes (like "ray_epsilon") updates would not change the geometry
        if (!attribute->updateRequiresGeomReload()) {
            continue;
        }
        // whether this attribute or its dependency is dirtied
        bool updateRequired = hasChanged(attribute) || hasBindingChanged(attribute);
        if (updateRequired) {
            return true;
        }

        switch (attribute->getType()) {
        case TYPE_SCENE_OBJECT:
            {
                const AttributeKey<SceneObject*> key(*attribute);
                SceneObject * const object = get(key);
                if (object) {
                    if (object->isA<Geometry>() &&
                        !object->asA<Geometry>()->requiresGeometryUpdate(sceneObjects, depth + 1)) {
                        continue;
                    }
                    updateRequired |= object->updatePrep(sceneObjects, depth + 1);
                }
            }
            break;

        case TYPE_SCENE_OBJECT_VECTOR:
            updateRequired |= geometryUpdatePrepSequenceContainer<SceneObjectVector>(
                attribute, sceneObjects, depth + 1);
            break;

        case TYPE_SCENE_OBJECT_INDEXABLE:
            updateRequired |= geometryUpdatePrepSequenceContainer<SceneObjectIndexable>(
                attribute, sceneObjects, depth + 1);
            break;

        default:
            break;
        }

        if (updateRequired) {
            return true;
        }
    }
    // This geometry does not have an attribute change that requires an update.
    // Change the flag to false.
    mAttributeTreeChanged = false;
    return false;
}

} // namespace rdl2
} // namespace scene_rdl2

