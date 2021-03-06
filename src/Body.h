﻿#pragma once

#include "Infrastructure/BoundingShapes.h"
#include "Infrastructure/Color.h"

#include "Object.h"

MM_BEGIN

class BodyType;
class Renderer;
struct Segment;

class IBodyRenderer
{
public:
	friend class Body;
	
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	
	MM_PROPERTY_PBV_NS(Body*, _body, Body)
};

/**
 * 在 ModernMagic 中，Body 代表了一个可以移动的具有确切的坐标、角度、速度的物体
 * Body 要求其派生类实现碰撞检测函数
 */
class Body : public UpdatableObject
{
	MM_TAG_OVERRIDE_UPDATE
	
public:
	Body();
	Body(const Body &other);
	~Body();
	
	/**
	 * 坐标
	 */
	MM_PROPERTY_PBR(Vector2, _position, Position)

	void SetPosition(float x, float y) {
		_position.X = x;
		_position.Y = y;
	}
	void SetX(float x) {
		_position.X = x;
	}
	void SetY(float y) {
		_position.Y = y;
	}
	
	/**
	 * 纹理ID
	 */
	MM_PROPERTY_PBV(int, _texture, Texture)
	
	/**
	 * 颜色
	 */
	MM_PROPERTY_PBR(Color, _color, Color)

	/**
	 * 缩放（比例）
	 */
	MM_PROPERTY_PBV(float, _scale, Scale)
	
	/**
	 * Body 所处的层
	 */
	MM_PROPERTY_PBV(int, _layer, Layer)
	
	/**
	 * 碰撞半径
	 */
	MM_PROPERTY_PBV(float, _radius, Radius)
	
	/**
	 * 角度
	 */
	MM_PROPERTY_PBV_US(float, _angle, Angle)
	
	/**
	 * 速度
	 */
	MM_PROPERTY_PBV_US(float, _speed, Speed)
	
	/**
	 * 角度加量
	 */
	MM_PROPERTY_PBV(float, _angleAddition, AngleAddition)
	
	/**
	 * 速度加量
	 */
	MM_PROPERTY_PBV(float, _speedAddition, SpeedAddition)
	
	/**
	 * 对象是否被冻结
	 */
	MM_PROPERTY_BOOL(_isFrozen, IsFrozen)
	
	/**
	 * 是否在对象移出屏幕时销毁卸载对象
	 */
	MM_PROPERTY_BOOL(_destroyWhenMoveOffScreen, IsDestroyWhenMoveOffScreen)
	
	/**
	 * 是否在其对象的时间轴结束后销毁对象
	 */
	MM_PROPERTY_BOOL(_destroyWhenTimelineEnd, IsDestroyWhenTimelineEnd)
	
	/**
	 * Body 应用的时间轴
	 * [注意：拷贝 Body 也会造成 Applied Timeline 的拷贝
	 *        一般情况下请不要为大量发射的子弹设置时间轴
	          而是将所有要控制的 Body 交由 TimerListener（Action） 管理]
	 */
	MM_PROPERTY_PBV_US(Timeline*, _appliedTimeline, AppliedTimeline)

	// 如果当前没有为 Body 设置时间轴，AppliedTimeline 函数会为其创建一个
	Timeline *AppliedTimeline();
	
	/**
	 * Body 是否是子弹
	 */
	MM_PROPERTY_BOOL_NS(_isBullet, IsBullet);
	
	/**
	 * Body 每秒的坐标偏移
	 */
	MM_PROPERTY_PBR_NS(Vector2, _calculatedOffset, CalculatedOffset)

	/**
	 * 不透明度 0.0~1.0
	 */
	MM_PROPERTY_PBV(float, _opacity, Opacity)
	
	/**
	 * 根据 Speed 与 Angle 计算 Body 每秒的坐标偏移
	 * 通常不需要手动调用
	 */
	virtual void Calculate();
	
	/**
	 * 判断当前 Body 是否与一个矩形发生碰撞
	 */
	virtual bool IsCollided(const BoundingBox &rect) const = 0;
	
	/**
	 * 判断当前 Body 是否与一个圆形发生碰撞
	 */
	virtual bool IsCollided(const Vector2 &pos, float r) const = 0;
	
	/**
	 * 判断当前 Body 是否与线段发生碰撞
	 */
	virtual bool IsCollided(const Segment &seg) const = 0;
	
	/**
	 * 设置 Body 的类型
	 */
	virtual void SetType(const String &name) = 0;
	
	/**
	 * 反弹一个Body
	 *
	 * @param 进行反弹的body
	 * @param 法线角度
	 */
	static void Rebound(Body *body, float normal) {
		body->SetAngle(normal * 2 - body->GetAngle());
	}
	
protected:
	virtual bool OnInstalling() override;
	void SetIsReboundable(bool v) { _isBullet = v; }
	
private:
	void InitProperties();
	bool _isNeedToCal;
};

MM_END
