#include "EditorWindow.hpp"

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>

#include <FL/Fl_Group.H>
#include <FL/Fl_Menu.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/filename.H>

class EditorWindow::FileBuffer : public Fl_Group {
public:
    FileBuffer(int x, int y, int w, int h, char *new_name, Fl_Text_Buffer *f_buff, const std::string path = {});
    ~FileBuffer();

private:
    Fl_Text_Editor *editor;
    std::string full_path;
};

EditorWindow::FileBuffer::FileBuffer(int x, int y, int w, int h, char *new_name, Fl_Text_Buffer *f_buff, const std::string path)
    : Fl_Group(x, y, w, h, new_name)
    , full_path(path) {
    editor = new Fl_Text_Editor(x, y, w, h);
    editor->buffer(f_buff);
    add(editor);
}

EditorWindow::FileBuffer::~FileBuffer() {
    free((void *)label());
    label(NULL);
}

static char *get_new_name();
/**
 * Construct a new Editor Window. If opened_buffers is empty, create new file buffer
 */
EditorWindow::EditorWindow(int w, int h, const char *t)
    : Fl_Double_Window(w, h, t) {
    // create main menu
    menu = init_menu(0, 0, w);
    buffers_tabs = new Fl_Tabs(0, 25, w, h - 25);
    resizable(buffers_tabs);
    show();
}

EditorWindow::~EditorWindow() {}

/**
 * Create new menu bar with callbacks
 */
Fl_Menu_Bar *EditorWindow::init_menu(int x, int y, int w, int h) {
    Fl_Menu_Bar *new_menu = new Fl_Menu_Bar(x, y, w, h);
    // new_menu->box(FL_FLAT_BOX);
    new_menu->add("File/&New File", FL_COMMAND + 'n', (Fl_Callback *)new_cb, (void *)this);
    new_menu->add("File/&Open File...", FL_COMMAND + 'o', (Fl_Callback *)open_cb, (void *)this, FL_MENU_DIVIDER);
    new_menu->add("File/&Save", FL_COMMAND + 's', save_cb, (void *)this);
    new_menu->add("File/&Save As...", FL_COMMAND + FL_SHIFT + 's', saveas_cb, (void *)this, FL_MENU_DIVIDER);
    new_menu->add("File/&Close", FL_COMMAND + 'q', close_cb, (void *)this);
    new_menu->add("File/&Quit", FL_COMMAND + FL_SHIFT + 'q', quit_cb);

    return new_menu;
}

void EditorWindow::create_empty() {
    FileBuffer *new_file = new FileBuffer(0, 25 + 25, this->w(), this->h() - 25 - 25, get_new_name(), new Fl_Text_Buffer);
    buffers_tabs->add(new_file);
    buffers_tabs->resizable(new_file);
}

void EditorWindow::new_cb(Fl_Widget *o, void *e) {
    // create new buffer
    EditorWindow *editor = (EditorWindow *)e;
    // FileBuffer *new_file = new FileBuffer(0, 25 + 25, editor->w(), editor->h() - 25 - 25, get_new_name(), new Fl_Text_Buffer);
    FileBuffer *new_file = new FileBuffer(0, 25 + 25, editor->w(), editor->h() - 25 - 25, get_new_name(), new Fl_Text_Buffer);
    editor->buffers_tabs->add(new_file);
    editor->buffers_tabs->resizable(new_file);
    editor->buffers_tabs->redraw();
}

void EditorWindow::open_cb(Fl_Widget *o, void *) {
    // open exiting file
}

void EditorWindow::save_cb(Fl_Widget *o, void *e) {
    // save existing file
}

void EditorWindow::saveas_cb(Fl_Widget *o, void *e) {
    // save file as new file
}

void EditorWindow::close_cb(Fl_Widget *o, void *e) {
    /// close current buffer
}

void EditorWindow::quit_cb(Fl_Widget *o, void *) {
    exit(0);
}

/**
 * Generate the new name for non saved buffer
 * 
 * @return char* - pointer to name string. Must be free()-d to avoid memory leak.
 */
static char *get_new_name() {
    static int number {1};
    static const char basename[] = "Unnamed-";
    char *new_name = NULL;
    asprintf(&new_name, "%s%d", basename, number);
    ++number;
    return new_name;
}