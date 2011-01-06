#if !defined(FENETRE_H_KSO4VZ2A)
#define FENETRE_H_KSO4VZ2A

#include <gtkmm.h>
#include <gtkmm/main.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/layout.h>
#include <cairomm/context.h>

struct fenetre {
	fenetre(int argc, char** argv);
	virtual ~fenetre() {}
private:
	Gtk::Main gtk_;
	Gtk::Window win_;
};

#endif /* end of include guard: FENETRE_H_KSO4VZ2A */
