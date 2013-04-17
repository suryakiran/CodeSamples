#ifndef RestSampleWindow_hxx_INCLUDED
#define RestSampleWindow_hxx_INCLUDED

#include <Window.hxx>

class SearchWidget;

class RestSampleWindow : public Window
{
public:
  RestSampleWindow(QWidget* parent = 0);

private:
  SearchWidget* widget;

protected:
  virtual bool eventFilter(QObject* object, QEvent* event);
};

#endif
