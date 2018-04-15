import java.awt.*;
import java.awt.event.*;
import com.jogamp.opengl.*;
import com.jogamp.opengl.awt.GLCanvas;
import com.jogamp.opengl.fixedfunc.*;
import com.jogamp.opengl.util.Animator;
import java.util.ArrayList;
import java.util.function.Function;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.lang.reflect.InvocationTargetException;

//public class glWin implements GLEventListener {
public class glWin implements GLEventListener {

   public glWin() {
        win = new MyWin(); 
        win.glModelList  = new ArrayList<>();
    }
 
    private final float rotateT = 0.0f;
    private final MyWin win;
    
    class MyWin
    {
        Frame   frame;
        int     x;
        int     y;
        int     width;
        int     height;
        GLCanvas canvas;
        Animator animator;
        Function OnResize = null;
        ArrayList<Class>    glModelList = null;
//        List<Class<? extends A>> classes = new ArrayList<Class<? extends A>>();
     };
    
//    void setOnResizeCB(Function func) {
//        win.OnResize = func;
//    }
//    
    
    void addGlModel(Class object) {
         boolean add = win.glModelList.add(object);
        System.out.print( win.glModelList.size() );
    }
    
    
    MyWin create(int x, int y, int width, int height) {
        /**
        * Création du Canvas OpenGL
        * pour pouvoir dessiner dessus
        */
        win.canvas = new GLCanvas();
        win.frame = new Frame("Jogl Quad drawing");
        // Création de l'Animator
        win.animator = new Animator(win.canvas);
        /**
         * Nous attachons ensuite le méchanisme de callback
         * à notre surface dessinable
         */
        win.canvas.addGLEventListener(this);
        /**
         * Nous attachons maintenant notre 
         * surface dessinable à notre fenêtre 
         */
        win.frame.add(win.canvas);
        /**
         * Taille et position de la fenêtre 
         * et nous l'affichons
         */
        win.frame.setLocation(x, y);
        win.frame.setSize(width, height);
        win.frame.setResizable(true);
        win.frame.addWindowListener(new WindowAdapter() {
                @Override
                public void windowClosing(WindowEvent e) {
                        win.animator.stop();
                        win.frame.dispose();
                        System.exit(0);
                }
        });
        win.frame.setVisible(true);
        /**
         * Nous démarrons l'Animator qui va se charger de faire des appels
         * à la méthode display();
         */
        win.animator.start();
        win.canvas.requestFocus();
        
        return win;
    }
    
    /**
     * display() sera appelée en boucle tout au long de l'application
     * par la classe Animator. C'est dans cette fonction qu'on fera
     * tout ce qui doit être affiché
     * @param glDrawable
     */
    @Override
    public void display(GLAutoDrawable glDrawable) {
         
//            final GL2 gl = gLDrawable.getGL().getGL2();
//            gl.glClear(GL.GL_COLOR_BUFFER_BIT);
//            gl.glClear(GL.GL_DEPTH_BUFFER_BIT);
//            gl.glLoadIdentity();
//            gl.glTranslatef(0.0f, 0.0f, -5.0f);
//
//            // rotate about the three axes
//            gl.glRotatef(rotateT, 1.0f, 0.0f, 0.0f);
//            gl.glRotatef(rotateT, 0.0f, 1.0f, 0.0f);
//            gl.glRotatef(rotateT, 0.0f, 0.0f, 1.0f);
//
//            // Draw A Quad
//            gl.glBegin(GL2.GL_QUADS);       
//            gl.glColor3f(0.0f, 1.0f, 1.0f);   // set the color of the quad
//            gl.glVertex3f(-1.0f, 1.0f, 0.0f);   // Top Left
//            gl.glVertex3f( 1.0f, 1.0f, 0.0f);   // Top Right
//            gl.glVertex3f( 1.0f,-1.0f, 0.0f);   // Bottom Right
//            gl.glVertex3f(-1.0f,-1.0f, 0.0f);   // Bottom Left
//            // Done Drawing The Quad
//            gl.glEnd();                                                     
//
//            // increasing rotation for the next iteration
//            rotateT += 0.2f;

                win.glModelList.forEach((Class obj) -> {
                try {
                    final java.lang.reflect.Method method;
                    method = obj.getMethod("display", GLAutoDrawable.class);
                    try {
                        method.invoke(obj.newInstance(), glDrawable);
                    } catch (InstantiationException | IllegalArgumentException | IllegalAccessException | InvocationTargetException ex) { 
                        Logger.getLogger(glWin.class.getName()).log(Level.SEVERE, null, ex);
                    }
                } catch (SecurityException | NoSuchMethodException ex) { 
                   Logger.getLogger(glWin.class.getName()).log(Level.SEVERE, null, ex);
                }
                });
                
    }

    /**
     * init() sera appelée une fois au début de l'animation
     * C'est dans cette méthode que nous nous chargerons de toute
     * les opérations d'initialisation
     * @param glDrawable
     */
    @Override
    public void init(GLAutoDrawable glDrawable) {
            GL2 gl = glDrawable.getGL().getGL2();
            gl.glShadeModel(GLLightingFunc.GL_SMOOTH);
            gl.glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            gl.glClearDepth(1.0f);
            gl.glEnable(GL.GL_DEPTH_TEST);
            gl.glDepthFunc(GL.GL_LEQUAL);
            gl.glHint(GL2ES1.GL_PERSPECTIVE_CORRECTION_HINT, GL.GL_NICEST);
    }

    /**
     * reshape() sera appelée si la fenêtre d'affichage est redimensionnée
     * @param gLDrawable
     * @param x
     * @param y
     * @param width
     * @param height
     */
    @Override
    public void reshape(GLAutoDrawable gLDrawable, int x, int y, int width, int height) {
//        if (win.OnResize != null)
//            cb.reshapeCB(gLDrawable, x, y, width, height);
            GL2 gl = gLDrawable.getGL().getGL2();
            final float aspect = (float) width / (float) height;
            gl.glMatrixMode(GLMatrixFunc.GL_PROJECTION);
            gl.glLoadIdentity();
            final float fh = 0.5f;
            final float fw = fh * aspect;
            gl.glFrustumf(-fw, fw, -fh, fh, 1.0f, 1000.0f);
            gl.glMatrixMode(GLMatrixFunc.GL_MODELVIEW);
            gl.glLoadIdentity();
    } 

    @Override
    public void dispose(GLAutoDrawable gLDrawable) {
    }
    
    /**
     * displayChanged() est appelée si le mode d'affichage par exemple
     * est modifié. Cependant nous n'implémenterons pas cette méthode.
     * @param drawable
     * @param modeChanged
     * @param deviceChanged
     */
    public void displayChanged(GLAutoDrawable drawable, boolean modeChanged,
                    boolean deviceChanged) {
    }

}

				