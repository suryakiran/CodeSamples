#ifndef TAB_FOCUS_WINDOW_HXX
#define TAB_FOCUS_WINDOW_HXX

#include <Window.hxx>

class TabWidget;

class TabFocusWindow : public Window
{
  public:
    TabFocusWindow(QWidget* parent = 0);

  private:
    TabWidget* widget;

  protected:
    virtual bool eventFilter (QObject* object, QEvent* event);
};

#endif
