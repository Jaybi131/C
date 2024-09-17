#include <gtk/gtk.h>
#include <math.h>

#define WIDTH 1910
#define HEIGHT 980
#define DT 0.05
#define G 0.2
//                  Sonne   Erde   Venus Merkur      Uranus
int planets[]={       1,     2,     3,  4,   5,     0};
double xcor[]={   1000.0, 1000.0, 1000.0,   1000.0, 1000.0};
double ycor[]={   456.0, 710.0, 279.0,      350.0,  230.0};
double xvel[]={   -0.2,  -1.55,   1.4,      1.0,    1.0};
double yvel[]={     0.0,   0.0,   0.0,      0.0,     0.0};
double mass[]={  180000, 10000,   700,      200,     400};

double fx=0;
double fy=0;

static void draw (GtkDrawingArea *drawing_area, cairo_t *c,
                  int width, int height, gpointer user_data)
{
    
    // Hintergrund schwarz füllen
  gdk_cairo_set_source_rgba(c, &(GdkRGBA){0.0, 0.0, 0.0, 1.0});
  cairo_rectangle(c, 0, 0, width, height);
  cairo_fill(c);
    
  GdkRGBA yellow = { 1.0, 0.8, 0.0, 1.0 };
  GdkRGBA blue = { 0.0, 0.5, 1.0, 1.0 };
  GdkRGBA brown  = { 0.357, 0.227, 0.161, 1.0 };
  GdkRGBA grey = { 0.5, 0.5, 0.5, 1.0 };
  GdkRGBA purple = {0.5, 0.0, 0.5, 1.0};

  gdk_cairo_set_source_rgba (c, &yellow);
  cairo_arc (c, xcor[0], ycor[0], 40, 0, 2 * G_PI);
  cairo_fill (c);
  gdk_cairo_set_source_rgba (c, &blue);
  cairo_arc (c, xcor[1], ycor[1], 12, 0, 2 * G_PI);
  cairo_fill (c);
  gdk_cairo_set_source_rgba (c, &grey);
  cairo_arc (c, xcor[2], ycor[2], 9, 0, 2 * G_PI);
  cairo_fill (c);
  gdk_cairo_set_source_rgba (c, &brown);
  cairo_arc (c, xcor[3], ycor[3], 6, 0, 2 * G_PI);
  cairo_fill (c);
  gdk_cairo_set_source_rgba (c, &purple);
  cairo_arc (c, xcor[4], ycor[4], 15, 0, 2 * G_PI);
  cairo_fill (c);
}

// Aktualisieren Sie die Koordinaten und Geschwindigkeiten der Planeten
gboolean timer (GtkWidget *widget)
{
  for (int i = 0; planets[i]; i++){
    for (int j = 0; planets[j]; j++){
        if(j!=i){
            //Distanz berechnen
            double distanz = sqrt(((xcor[j]-xcor[i])*(xcor[j]-xcor[i])) + ((ycor[j]-ycor[i])*(ycor[j]-ycor[i])));
            //printf("Distanz: %f\n",distanz);
            //Kraft in x/y Richtung
            double fx_teil = (mass[j]*mass[i]*G*(xcor[j]-xcor[i]))/(distanz*distanz*distanz);
            double fy_teil = (mass[j]*mass[i]*G*(ycor[j]-ycor[i]))/(distanz*distanz*distanz);
            //Summe für alle Kräfte von einem Planeten zu allen anderen
            fx += fx_teil;
            fy += fy_teil;
            //printf("fx_teil: %f\n",fx_teil);
            //printf("fy_teil: %f\n",fy_teil);
        }
    }                                                               
      //Geschwindigkeit berechnen
      xvel[i]+=(fx/mass[i])*DT;
      yvel[i]+=(fy/mass[i])*DT;

      //Kräfte clearen
      fx=0;
      fy=0;
      //printf("\n");
  }//Ort berechnen
  for (int i = 0; planets[i];i++){
      xcor[i]+=xvel[i]*100*DT;
      ycor[i]+=yvel[i]*100*DT;
  }
  
  gtk_widget_queue_draw (widget);
  return TRUE;
}

static void activate (GtkApplication *app, gpointer user_data)
{
  GtkWidget *window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Paralleluniversum");

  GtkWidget *vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
  gtk_window_set_child (GTK_WINDOW (window), vbox);

  GtkWidget *drawing_area = gtk_drawing_area_new ();
  gtk_widget_set_size_request (drawing_area, WIDTH, HEIGHT);
  gtk_drawing_area_set_draw_func (GTK_DRAWING_AREA (drawing_area), draw, NULL, NULL);
  gtk_box_append (GTK_BOX (vbox), drawing_area);

  GtkWidget *quit_button = gtk_button_new_with_label ("Quit");
  g_signal_connect_swapped (quit_button, "clicked", G_CALLBACK (gtk_window_destroy), window);
  gtk_box_append (GTK_BOX (vbox), quit_button);

  g_timeout_add (50, (GSourceFunc) timer, drawing_area);

  gtk_window_present (GTK_WINDOW (window));
}
//Dieser Code ist für die Grundstruktur einer GTK-Anwendung verantwortlich und stellt deren Initialisierung und Ausführung sicher.
int main (int argc, char **argv)
{
  GtkApplication *app = gtk_application_new ("de.hs-bochum.cvh.hp.hello-gtk", G_APPLICATION_DEFAULT_FLAGS); // Erstellt eine neue GtkApplication-Instanz. Dieses Objekt stellt die Basis für eine GTK-Anwendung dar.
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL); // Richtet einen Signalhandler für das App-Objekt ein. In diesem Fall wird das Signal „activate“ erwartet, das beim Aktivieren der Anwendung ausgelöst wird. Der Signalhandler ist die Aktivierungsfunktion.
  int status = g_application_run (G_APPLICATION (app), argc, argv); // Startet die Ausführung einer GTK-Anwendung. Diese Funktion verarbeitet Ereignisse, Benutzerinteraktionen und die Steuerung der Anwendungsausführung
  g_object_unref (app); // Dekrementiert den Referenzzähler des App-Objekts. Wenn der Referenzzähler Null erreicht, wird das Objekt aus dem Speicher freigegeben.
  return status;
}
