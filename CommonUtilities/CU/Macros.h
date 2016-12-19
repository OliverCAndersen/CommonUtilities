#pragma once

#define SAFE_DELETE(p) delete p; p = nullptr;

#define CLAMP(x, a, b)   (((x) < (a)) ? (a) : (((x) > (b)) ? (b) : (x)));