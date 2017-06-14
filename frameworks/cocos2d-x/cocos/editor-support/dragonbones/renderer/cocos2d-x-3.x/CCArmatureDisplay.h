#ifndef DRAGONBONES_CC_ARMATURE_DISPLAY_CONTAINER_H
#define DRAGONBONES_CC_ARMATURE_DISPLAY_CONTAINER_H

#include "dragonBones/DragonBonesHeaders.h"
#include "cocos2d.h"
#include "CCEventObject.h"

DRAGONBONES_NAMESPACE_BEGIN

class CCArmatureDisplay : public cocos2d::Node, public IArmatureDisplay
{
private:
	typedef std::function<void(cocos2d::Ref* sender, CCEventObject* cceventobj, const std::string type, const std::string name)> ccDragonEventCallback;
	ccDragonEventCallback _dragonEventCallback;
	void _animationEventHandler(cocos2d::EventCustom* event) const;

	CCEventObject* _ccEventObject;
public:
    /** @private */
    static CCArmatureDisplay* create();

public:
    /** @private */
    Armature* _armature;

protected:
    cocos2d::EventDispatcher* _dispatcher;

protected:
    CCArmatureDisplay();
    virtual ~CCArmatureDisplay();

private:
    DRAGONBONES_DISALLOW_COPY_AND_ASSIGN(CCArmatureDisplay);

public:
    /** @private */
    virtual void _onClear() override;
    /** @private */
    virtual void _dispatchEvent(EventObject* value) override;
    /** @private */
    virtual void dispose() override;
    /** @private */
    virtual void update(float passedTime) override;

public:
    virtual void advanceTimeBySelf(bool on) override;
    void addEvent(const std::string& type, const std::function<void(EventObject*)>& callback);
    void removeEvent(const std::string& type);

    inline bool hasEvent(const std::string& type) const override
    {
        return _dispatcher->isEnabled();
    }

    inline Armature* getArmature() const override 
    {
        return _armature;
    }

    virtual Animation& getAnimation() const override 
    {
        return _armature->getAnimation();
    }

	inline Animation* lua_getAnimation() const
	{
		return &(_armature->getAnimation());
	}

	void bindDragonEventListener(const ccDragonEventCallback& callback);

	void addDragonEventType(const std::string& type);

	void removeDragonEventType(const std::string& type);
};

/** @private */
class DBCCSprite : public cocos2d::Sprite
{
public:
    /** @private */
    static DBCCSprite* create();

protected:
    DBCCSprite();
    virtual ~DBCCSprite();

private:
    DRAGONBONES_DISALLOW_COPY_AND_ASSIGN(DBCCSprite);

    /**
    * Modify for polyInfo rect
    */
    bool _checkVisibility(const cocos2d::Mat4& transform, const cocos2d::Size& size, const cocos2d::Rect& rect);

public:
    /**
     * Modify for polyInfo rect
     */
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
    /**
     * Modify for cocos2dx 3.7, 3.8, 3.9
     */
    cocos2d::PolygonInfo& getPolygonInfoModify();
};

DRAGONBONES_NAMESPACE_END
#endif // DRAGONBONES_CC_ARMATURE_DISPLAY_CONTAINER_H
