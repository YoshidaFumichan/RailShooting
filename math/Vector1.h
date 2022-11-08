#pragma once
#include <DirectXMath.h>
#include <vector>


// 補完関数
// 線形補完(1次関数補完)
const float& lerp(const float& start, const float& end, const float& t);
// イーズイン(2次関数補完)
const float& easeIn(const float& start, const float& end, const float& t);
// イーズアウト(2次関数補完)
const float& easeOut(const float& start, const float& end, const float& t);
// イーズインアウト(2次関数補完)
const float& easeInOut(const float& start, const float& end, const float& t);