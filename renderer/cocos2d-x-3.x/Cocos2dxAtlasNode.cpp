
#include "2d/CCSpriteFrame.h"
#include "base/CCDirector.h"
#include "math/TransformUtils.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCTextureAtlas.h"
#include "renderer/CCTextureCache.h"

#include "renderer/Cocos2dxAtlasNode.h"

NS_CC_BEGIN

// implementation Cocos2dxAtlasNode

// Cocos2dxAtlasNode - Creation & Init

Cocos2dxAtlasNode::Cocos2dxAtlasNode()
: m_pTextureAtlas(NULL)
, m_bIgnoreContentScaleFactor(false)
{
}

Cocos2dxAtlasNode::~Cocos2dxAtlasNode()
{
    CC_SAFE_RELEASE(m_pTextureAtlas);
}

Cocos2dxAtlasNode * Cocos2dxAtlasNode::create(TextureAtlas* textureAtlas , unsigned int quadIndex , const Rect &sourceRect)
{
    Cocos2dxAtlasNode * pRet = new Cocos2dxAtlasNode();
    if (pRet->initWithTextureAtlas(textureAtlas , quadIndex , sourceRect))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool Cocos2dxAtlasNode::initWithTextureAtlas(TextureAtlas* textureAtlas , unsigned int quadIndex , const Rect &sourceRect)
{
    
    m_pTextureAtlas = textureAtlas;

    if (! m_pTextureAtlas)
    {
        CCLOG("cocos2d: Could not initialize Cocos2dxAtlasNode. Invalid Texture.");
        return false;
    }
    m_pTextureAtlas->retain();
    auto size = sourceRect.size;
    auto spriteFrame = SpriteFrame::createWithTexture(textureAtlas->getTexture(), sourceRect, false, Vec2::ZERO, size);
    if (initWithSpriteFrame(spriteFrame))
    {
        return true;
    }
    return false;
}

void Cocos2dxAtlasNode::setIgnoreContentScaleFactor(bool bIgnoreContentScaleFactor)
{
    m_bIgnoreContentScaleFactor = bIgnoreContentScaleFactor;
}


NS_CC_END
