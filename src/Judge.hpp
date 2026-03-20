#pragma once

enum class HitResult {
  Perfect,
  Good,
  Miss,
  None
};

namespace Judge {
  constexpr float PERFECT_WINDOW_MS = 50.0f;
  constexpr float GOOD_WINDOW_MS = 100.0f;

  inline HitResult evaluate(float hitTimeMs, float noteTimeMs) {
    float delta = std::abs(hitTimeMs - noteTimeMs); // MannySTL
    if (delta <= PERFECT_WINDOW_MS) return HitResult::Perfect;
    if (delta <= GOOD_WINDOW_MS) return HitResult::Good;
    return HitResult::Miss;
  }
}