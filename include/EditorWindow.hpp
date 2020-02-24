#include <string>

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Text_Editor.H>

class EditorWindow : public Fl_Double_Window {
 public:
    EditorWindow(int w, int h, const char *t);
    ~EditorWindow();

 private:
    class FileTab; // represent opened buffer
    enum { menu_height = 25, tab_height = 25 };

    Fl_Menu_Bar *menu;
    Fl_Tabs *buffers_tabs;
    // init gui
    Fl_Menu_Bar *init_menu(int x, int y, int w, int h = menu_height);
    Fl_Tabs *init_tabs(int x, int y, int w, int h);
    // common
    void create_new(const std::string &path = {});
    void save();
    void saveas();
    void close();
    // menu callbacks, must be static
    static void new_cb(Fl_Widget *o, void *);
    static void open_cb(Fl_Widget *o, void *);
    static void save_cb(Fl_Widget *o, void *);
    static void saveas_cb(Fl_Widget *o, void *);
    static void close_cb(Fl_Widget *o, void *);
    static void quit_cb(Fl_Widget *o, void *);
    // other
    static char *get_new_name();
};

class EditorWindow::FileTab : public Fl_Group {
 public:
    FileTab(int x, int y, int w, int h, const std::string &path = {});
    ~FileTab();

    Fl_Text_Editor *editor() { return editor_; };
    std::string full_path() { return full_path_; };
    void full_path(const std::string &new_path);

 private:
    Fl_Text_Buffer *buffer_;
    Fl_Text_Editor *editor_;
    std::string full_path_;
};