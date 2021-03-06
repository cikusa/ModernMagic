﻿#include "stdafx.h"

#include "Bullet.h"

#include "Timeline/Timeline.h"
#include "Infrastructure/Segment.h"

MM_BEGIN

Bullet::Bullet():
	_type(nullptr), _colReBoard(nullptr)
{
	this->InitProperties();
}

Bullet::Bullet(const Bullet &other):
	Body(other),
	_type(other._type), _colReBoard(other._colReBoard)
{
	this->InitProperties();
}

void Bullet::InitProperties()
{
	this->RegisterPropertySetter<String> (
		"Type",
		std::bind(&Bullet::SetType, this, std::placeholders::_1)
	);
}

MM_IMPL_CLONE(Bullet)
{
	return theMMBulletPool.Construct(*this);
}

MM_IMPL_DESTROY(Bullet)
{
	theMMBulletPool.Delete(this);
}

bool Bullet::IsCollided(Bullet *other) const
{
	return this->IsCollided(other->GetPosition(), other->GetRadius());
}

bool Bullet::IsCollided(const BoundingBox &rect) const
{
	return rect.Intersects(this->GetPosition(), this->GetRadius());
}

bool Bullet::IsCollided(const Vector2 &pos, float r) const
{
	return Vector2::Distance(this->GetPosition(), pos) < (this->GetRadius() + r);
}

bool Bullet::IsCollided(const Segment &seg) const
{
	return seg.Intersects(this->GetPosition(), this->GetRadius());
}

MM_END
