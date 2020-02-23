#include "EditorWindow.hpp"

#include <cstring>

#include <FL/Fl_Group.H>
#include <FL/Fl_Menu.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/filename.H>

// Construct a new Editor Window. If opened_buffers is empty, create new file buffer
EditorWindow::EditorWindow(int w, int h, const char *t)
        : Fl_Double_Window(w, h, t) {
    // create main menu
    menu = init_menu(0, 0, w);
    buffers_tabs = init_tabs(0, 0 + menu_height, w, h - menu_height);
    resizable(buffers_tabs);
    if (!buffers_tabs->children()) {
        create_new();
    }
    show();
}

EditorWindow::~EditorWindow() {}

// Create new menu bar with callbacks
Fl_Menu_Bar *EditorWindow::init_menu(int x, int y, int w, int h) {
    Fl_Menu_Bar *new_menu = new Fl_Menu_Bar(x, y, w, h);
    new_menu->box(FL_FLAT_BOX);
    new_menu->add("File/&New File", FL_COMMAND + 'n', (Fl_Callback *)new_cb, (void *)this);
    new_menu->add("File/&Open File...", FL_COMMAND + 'o', (Fl_Callback *)open_cb, (void *)this, FL_MENU_DIVIDER);
    new_menu->add("File/&Save", FL_COMMAND + 's', save_cb, (void *)this);
    new_menu->add("File/&Save As...", FL_COMMAND + FL_SHIFT + 's', saveas_cb, (void *)this, FL_MENU_DIVIDER);
    new_menu->add("File/Close", FL_COMMAND + 'q', close_cb, (void *)this);
    new_menu->add("File/&Quit", FL_COMMAND + FL_SHIFT + 'q', quit_cb);

    return new_menu;
}

Fl_Tabs *EditorWindow::init_tabs(int x, int y, int w, int h) {
    Fl_Tabs *new_tabs = new Fl_Tabs(x, y, w, h);
    new_tabs->box(FL_THIN_UP_BOX);
    new_tabs->selection_color(FL_WHITE);
    return new_tabs;
}

void EditorWindow::create_new(const std::string &path) {
    int draw_pos = menu_height + tab_height;
    FileTab *new_file = new FileTab(0, draw_pos, this->w(), this->h() - draw_pos, path);
    buffers_tabs->add(new_file);
    buffers_tabs->resizable(new_file);
    buffers_tabs->value(new_file);
    buffers_tabs->redraw();
    redraw();
}

void EditorWindow::save() {
    FileTab *current = (FileTab *)buffers_tabs->value();
    if (!current->full_path().empty()) {
        current->editor()->buffer()->savefile(current->full_path().data());
    } else {
        saveas();
    }
}

void EditorWindow::saveas() {
    // choose file name
    Fl_Native_File_Chooser file_chooser;
    file_chooser.title("Choose file name");
    file_chooser.type(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);
    if (file_chooser.show()) {
        return;
    }

    // set new filepath FileTab, get name from path, save buffer to file
    FileTab *current = (FileTab *)buffers_tabs->value();
    current->full_path(file_chooser.filename());
    redraw();
}

void EditorWindow::close() {
    FileTab *current = (FileTab *)buffers_tabs->value();
    if (!current) {
        // no buffers
        return;
    }
    buffers_tabs->remove(current);
    Fl::delete_widget(current);
    redraw();
}

void EditorWindow::new_cb(Fl_Widget *o, void *e) {
    // create new buffer
    EditorWindow *editor = (EditorWindow *)e;
    editor->create_new();
}

void EditorWindow::open_cb(Fl_Widget *o, void *e) {
    // open existing file
    EditorWindow *editor = (EditorWindow *)e;

    Fl_Native_File_Chooser file_chooser;
    file_chooser.title("Choose file to open");
    file_chooser.type(Fl_Native_File_Chooser::BROWSE_FILE);
    if (file_chooser.show()) {
        return;
    }
    editor->create_new({file_chooser.filename()});
}

void EditorWindow::save_cb(Fl_Widget *o, void *e) {
    // save existing file
    EditorWindow *editor = (EditorWindow *)e;
    editor->save();
}

void EditorWindow::saveas_cb(Fl_Widget *o, void *e) {
    // save file as new file
    EditorWindow *editor = (EditorWindow *)e;
    editor->saveas();
}

void EditorWindow::close_cb(Fl_Widget *o, void *e) {
    /// close current buffer
    EditorWindow *editor = (EditorWindow *)e;
    editor->close();
}

void EditorWindow::quit_cb(Fl_Widget *o, void *) {
    exit(0);
}

/**
 * Generate the new name for non saved buffer
 * 
 * @return char* - pointer to name string. Must be free()-d to avoid memory leak.
 */
char *EditorWindow::get_new_name() {
    static int number {1};
    static const char basename[] = "Unnamed-";
    char *new_name = NULL;
    asprintf(&new_name, "%s%d", basename, number);
    ++number;
    return new_name;
}