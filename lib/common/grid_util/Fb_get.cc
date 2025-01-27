// Copyright 2023 DreamWorks Animation LLC
// SPDX-License-Identifier: Apache-2.0

//
//
#include "Fb.h"

namespace scene_rdl2 {
namespace grid_util {

fb_util::RenderColor
Fb::getPixRenderBuffer(int sx, int sy) const
{
    fb_util::Tiler tiler(getWidth(), getHeight());
    unsigned tileOfs = tiler.linearCoordsToTiledOffset(sx, sy);
    const float *srcPix =
        reinterpret_cast<const float *>(mRenderBufferTiled.getData()) + tileOfs * 4;

    return fb_util::RenderColor(srcPix[0], srcPix[1], srcPix[2], srcPix[3]);
}

float
Fb::getPixPixelInfo(int sx, int sy) const
{
    fb_util::Tiler tiler(getWidth(), getHeight());
    unsigned tileOfs = tiler.linearCoordsToTiledOffset(sx, sy);
    const float *srcPix =
        reinterpret_cast<const float *>(mPixelInfoBufferTiled.getData()) + tileOfs * 1;

    return srcPix[0];
}

float
Fb::getPixHeatMap(int sx, int sy) const
{
    fb_util::Tiler tiler(getWidth(), getHeight());
    unsigned tileOfs = tiler.linearCoordsToTiledOffset(sx, sy);
    const float *srcPix =
        reinterpret_cast<const float *>(mHeatMapSecBufferTiled.getData()) + tileOfs * 1;

    return srcPix[0];
}

float
Fb::getPixWeightBuffer(int sx, int sy) const
{
    fb_util::Tiler tiler(getWidth(), getHeight());
    unsigned tileOfs = tiler.linearCoordsToTiledOffset(sx, sy);
    const float *srcPix =
        reinterpret_cast<const float *>(mWeightBufferTiled.getData()) + tileOfs * 1;

    return srcPix[0];
}

fb_util::RenderColor
Fb::getPixRenderBufferOdd(int sx, int sy) const
{
    fb_util::Tiler tiler(getWidth(), getHeight());
    unsigned tileOfs = tiler.linearCoordsToTiledOffset(sx, sy);
    const float *srcPix =
        reinterpret_cast<const float *>(mRenderBufferOddTiled.getData()) + tileOfs * 4;

    return fb_util::RenderColor(srcPix[0], srcPix[1], srcPix[2], srcPix[3]);
}

} // namespace grid_util
} // namespace scene_rdl2

