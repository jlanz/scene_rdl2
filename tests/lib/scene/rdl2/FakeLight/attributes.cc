// Copyright 2023 DreamWorks Animation LLC
// SPDX-License-Identifier: Apache-2.0


#include <scene_rdl2/scene/rdl2/rdl2.h>

using namespace scene_rdl2;

RDL2_DSO_ATTR_DECLARE

    rdl2::AttributeKey<rdl2::Float> attrFakeness;

RDL2_DSO_ATTR_DEFINE(rdl2::Light)

    attrFakeness =
        sceneClass.declareAttribute<rdl2::Float>("fakeness", 11);

RDL2_DSO_ATTR_END

