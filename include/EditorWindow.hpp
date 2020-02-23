#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Menu_Bar.H>

/**
 * Class to represent a text editor window
 */
class EditorWindow : public Fl_Double_Window {
public:
    EditorWindow(int w, int h, const char *t);
    ~EditorWindow();

private:
    class FileBuffer;

    Fl_Menu_Bar *menu;
    Fl_Tabs *buffers_tabs; // for view editing buffers

    Fl_Menu_Bar *init_menu(int x, int y, int w, int h = 25);
    void create_empty();

    // callbacks
    static void new_cb(Fl_Widget *o, void *);
    static void open_cb(Fl_Widget *o, void *);
    static void save_cb(Fl_Widget *o, void *);
    static void saveas_cb(Fl_Widget *o, void *);
    static void close_cb(Fl_Widget *o, void *);
    static void quit_cb(Fl_Widget *o, void *);
};