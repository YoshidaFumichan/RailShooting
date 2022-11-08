#pragma once
#include <DirectXMath.h>
#include <vector>


// �⊮�֐�
// ���`�⊮(1���֐��⊮)
const float& lerp(const float& start, const float& end, const float& t);
// �C�[�Y�C��(2���֐��⊮)
const float& easeIn(const float& start, const float& end, const float& t);
// �C�[�Y�A�E�g(2���֐��⊮)
const float& easeOut(const float& start, const float& end, const float& t);
// �C�[�Y�C���A�E�g(2���֐��⊮)
const float& easeInOut(const float& start, const float& end, const float& t);