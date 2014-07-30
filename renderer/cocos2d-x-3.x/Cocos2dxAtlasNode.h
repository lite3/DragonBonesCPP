
#ifndef __COCOS2DX_ATLAS_NODE_H__
#define __COCOS2DX_ATLAS_NODE_H__

#include "2d/CCSprite.h"
#include "base/CCProtocols.h"
#include "base/ccTypes.h"
#include "math/Mat4.h"
#include "renderer/CCTextureAtlas.h"
#include "renderer/CCQuadCommand.h"
#include "utils/preDB.h"
#include "utils/BytesType.h"
NS_CC_BEGIN

/**
 * @addtogroup base_nodes
 * @{
 */


/** @brief Cocos2dxAtlasNode is a subclass of CCNode that implements the CCRGBAProtocol and CCTextureProtocol protocol

It knows how to render a TextureAtlas object.
If you are going to render a TextureAtlas consider subclassing Cocos2dxAtlasNode (or a subclass of Cocos2dxAtlasNode)

All features from CCNode are valid, plus the following features:
- opacity and RGB colors
*/
class Cocos2dxAtlasNode : public Sprite
{
protected:
    TextureAtlas* m_pTextureAtlas;


    // This varible is only used for CCLabelAtlas FPS display. So plz don't modify its value.
    bool m_bIgnoreContentScaleFactor;


public:
    Cocos2dxAtlasNode();
    virtual ~Cocos2dxAtlasNode();

    /** creates a Cocos2dxAtlasNode  with an Atlas file the width and height of each item and the quantity of items to render*/
    static Cocos2dxAtlasNode * create(TextureAtlas* textureAtlas , unsigned int quadIndex , const Rect &sourceRect);
    bool initWithTextureAtlas(TextureAtlas* textureAtlas , unsigned int quadIndex , const Rect &sourceRect);
    

    
    // Overrides
    //virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
   

private :
    void updateOpacityModifyRGB();
    
    friend class Director;
    void setIgnoreContentScaleFactor(bool bIgnoreContentScaleFactor);
};

// end of base_node group
/// @}

NS_CC_END

#endif // __CCATLAS_NODE_H__


