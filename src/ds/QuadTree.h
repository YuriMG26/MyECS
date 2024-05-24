#pragma once

#include <array>
#include <cstdint>
#include <list>
#include <memory>
#include <utility>
#include <vector>

#include "../../vendor/raylib/include/raylib.h"

static bool RectangleContains(const Rectangle& a, const Rectangle& b);

#define MAX_DEPTH 8

template <typename T>
class QuadTree {
 public:
  QuadTree(Rectangle size = Rectangle{0.0f, 0.0f, 100.0f, 100.0f},
           const size_t depth = 0)
      : m_Depth(depth) {
    Resize(size);
  }

  void Resize(const Rectangle& area) {
    Clear();
    m_Rect = area;

    Vector2 childSize = Vector2{m_Rect.width / 2.0f, m_Rect.height / 2.0f};

    m_rChild = {
        Rectangle{m_Rect.x, m_Rect.x, childSize.x, childSize.y},
        Rectangle{m_Rect.x + childSize.x, m_Rect.y, childSize.x, childSize.y},
        Rectangle{m_Rect.x, m_Rect.y + childSize.y, childSize.x, childSize.y},
        Rectangle{m_Rect.x + childSize.x, m_Rect.y + childSize.y, childSize.x,
                  childSize.y},
    };
  }

  void Clear() {
    m_pItems.clear();
    for (uint8_t i = 0; i < 4; ++i) {
      if (m_pChild[i]) m_pChild[i]->clear();
      m_pChild[i].reset();
    }
  }

  size_t Size() const {
    size_t count = m_pItems.size();
    for (uint8_t i = 0; i < 4; ++i) {
      if (m_pChild[i]) count += m_pChild[i]->Size();
    }
  }

  void Insert(const T& item, const Rectangle& rect) {
    for (uint8_t i = 0; i < 4; ++i) {
      if (RectangleContains(m_rChild[i], rect)) {
        if (m_Depth + 1 < MAX_DEPTH) {
          if (!m_pChild[i]) {
            m_pChild[i] =
                std::make_shared<QuadTree<T>>(m_rChild[i], m_Depth + 1);
          }

          m_pChild[i]->Insert(item, rect);
          return;
        }
      }
    }

    m_pItems.push_back({rect, item});
  }

  std::list<T> Search(const Rectangle& rect) const {
    std::list<T> listItems;
    Search(rect, listItems);
    return listItems;
  }

  void Search(const Rectangle& rect, std::list<T>& listItems) const {
    for (const auto& p : m_pItems) {
    }
  }

 protected:
  size_t m_Depth = 0;

  Rectangle m_Rect;
  std::array<Rectangle, 4> m_rChild{};

  std::array<std::shared_ptr<QuadTree<T>>, 4> m_pChild;

  // TODO: better container and alternative to pair?
  std::vector<std::pair<Rectangle, T>> m_pItems;
};

static bool RectangleContains(const Rectangle& a, const Rectangle& b) {
  return ((a.x >= b.x) && (a.x + a.width < b.x + b.width) && (a.y >= b.y) &&
          (a.y + a.height < b.y + b.height));
}
