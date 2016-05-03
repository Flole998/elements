/*=================================================================================================
   Copyright (c) 2016 Joel de Guzman

   Licensed under a Creative Commons Attribution-ShareAlike 4.0 International.
   http://creativecommons.org/licenses/by-sa/4.0/
=================================================================================================*/
#if !defined(PHOTON_GUI_LIB_WIDGET_LAYER_APRIL_16_2016)
#define PHOTON_GUI_LIB_WIDGET_LAYER_APRIL_16_2016

#include <photon/widget/widget.hpp>
#include <memory>
#include <algorithm>

namespace photon
{
   ////////////////////////////////////////////////////////////////////////////////////////////////
   // Layer
   ////////////////////////////////////////////////////////////////////////////////////////////////
   class layer_widget : public composite
   {
   public:

      layer_widget() {}
      ~layer_widget() {}

      virtual rect         limits(basic_context const& ctx) const;
      virtual void         layout(context const& ctx);
      virtual hit_info     hit_element(context const& ctx, point const& p) const;
      virtual rect         bounds_of(context const& ctx, std::size_t index) const;
      virtual bool         scroll(context const& ctx, point const& p);
      virtual bool         focus(focus_request r);

   private:

      void                 focus_top();
      rect                 bounds;
   };

   template <typename... W>
   inline widget_ptr layer(W const&... elements)
   {
      auto p = new layer_widget{};
      std::vector<widget_ptr> v = { elements... };
      std::reverse(v.begin(), v.end());
      std::swap(v, p->elements());
      return widget_ptr{ p };
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////
   // Deck
   ////////////////////////////////////////////////////////////////////////////////////////////////
   class deck_widget : public layer_widget
   {
   public:

      deck_widget() : _selected_index(0) {}
      ~deck_widget() {}

      virtual void         draw(context const& ctx);
      void                 select(std::size_t index);

   private:

      std::size_t          _selected_index;
   };

   template <typename... W>
   inline widget_ptr deck(W const&... elements)
   {
      auto p = new deck_widget{};
      std::vector<widget_ptr> v = { elements... };
      std::reverse(v.begin(), v.end());
      std::swap(v, p->elements());
      return widget_ptr{ p };
   }
}

#endif