#pragma once

template<class T>
T Clamp(T a, T b, T v)
{ return v < a ? a : (v > b ? b : v); }