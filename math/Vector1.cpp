#include "Vector1.h"


const float& lerp(const float& start, const float& end, const float& t)
{
	return start * (1.0f - t) + end * t;
}

// �C�[�Y�C�� (�񎟕��)
const float& easeIn(const float& start, const float& end, const float& t)
{
	float y = t * t;
	return start * (1.0f - y) + end * y;
}

// �C�[�Y�A�E�g (�񎟕��)
const float& easeOut(const float& start, const float& end, const float& t)
{
	float y = t * (2 - t);
	return start * (1.0f - y) + end * y;
}

// �C�[�Y�C���A�E�g (�񎟕��)
const float& easeInOut(const float& start, const float& end, const float& t)
{
	float y = (t * t) * (3.0f - 2.0f * t);
	return start * (1.0f - y) + end * y;
}