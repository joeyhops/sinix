#ifndef _SINIX_GUI_WIDGET_H_
#define _SINIX_GUI_WIDGET_H_

#include <common/types.h>
#include <common/graphicscontext.h>
#include <drivers/keyboard.h>

namespace sinix {
  namespace gui {
    class Widget : public sinix::drivers::KeyboardEventHandler {
      protected:
        Widget* parent;
        sinix::common::int32_t x;
        sinix::common::int32_t y;
        sinix::common::int32_t w;
        sinix::common::int32_t h;

        sinix::common::uint8_t r;
        sinix::common::uint8_t g;
        sinix::common::uint8_t b;
        
        bool focusable;
      public:
        Widget(Widget* parent, sinix::common::int32_t x, sinix::common::int32_t y, sinix::common::int32_t w, sinix::common::int32_t h, sinix::common::uint8_t r, sinix::common::uint8_t g, sinix::common::uint8_t b);
        ~Widget();

        virtual void GetFocus(Widget* widget);
        virtual void ModelToScreen(sinix::common::int32_t &x, sinix::common::int32_t &y);

        virtual void Draw(sinix::common::GraphicsContext* gc);
        
        virtual bool ContainsCoordinate(sinix::common::int32_t x, sinix::common::int32_t y);
        virtual void OnMouseDown(sinix::common::int32_t x, sinix::common::int32_t y, sinix::common::uint8_t button);
        virtual void OnMouseUp(sinix::common::int32_t x, sinix::common::int32_t y, sinix::common::uint8_t button);
        virtual void OnMouseMove(sinix::common::int32_t oldx, sinix::common::int32_t oldy, sinix::common::int32_t newx, sinix::common::int32_t newy);
    };

    class CompositeWidget : public Widget {
      private:
        Widget* children[100];
        int numChildren;
        Widget* focusedChild;

      public:
        CompositeWidget(Widget* parent, sinix::common::int32_t x, sinix::common::int32_t y, sinix::common::int32_t w, sinix::common::int32_t h, sinix::common::uint8_t r, sinix::common::uint8_t g, sinix::common::uint8_t b);
        ~CompositeWidget();

        virtual void GetFocus(Widget* widget);
        virtual bool AddChild(Widget* child);

        virtual void Draw(sinix::common::GraphicsContext* gc);
        virtual void OnMouseDown(sinix::common::int32_t x, sinix::common::int32_t y, sinix::common::uint8_t button);
        virtual void OnMouseUp(sinix::common::int32_t x, sinix::common::int32_t y, sinix::common::uint8_t button);
        virtual void OnMouseMove(sinix::common::int32_t oldx, sinix::common::int32_t oldy, sinix::common::int32_t newx, sinix::common::int32_t newy);
        
        virtual void OnKeyDown(char);
        virtual void OnKeyUp(char);
    };
  }
}

#endif
