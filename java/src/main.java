import com.jogamp.opengl.GL2;
import com.jogamp.opengl.GLAutoDrawable;
import com.jogamp.opengl.fixedfunc.GLMatrixFunc;

//----------------------------------------------------------------------------
 
public class main {
    static final int   WIN_XPOS    = 100;
static final    int   WIN_YPOS    = 100;
static final    int   WIN_XRES    = 640;
static final    int   WIN_YRES    = 480;
static glWin    WinGL = new glWin();
static glScene  SceneGL;
        
public interface CallbackGL
{
    // This is just a regular method so it can return something or
    // take arguments if you like.
    public void reshapeCB (GLAutoDrawable gLDrawable, int x, int y, int width, int height);
}

    void reshapeCB (GLAutoDrawable gLDrawable, int x, int y, int width, int height)
    {
            GL2 gl = gLDrawable.getGL().getGL2();
            final float aspect = (float) width / (float) height;
            gl.glMatrixMode(GLMatrixFunc.GL_PROJECTION);
            gl.glLoadIdentity();
            final float fh = 0.5f;
            final float fw = fh * aspect;
            gl.glFrustumf(-fw, fw, -fh, fh, 1.0f, 1000.0f);
            gl.glMatrixMode(GLMatrixFunc.GL_MODELVIEW);
            gl.glLoadIdentity();

//        Win->width = width;
//        Win->height = height;
//
//        glMatrixMode(GL_PROJECTION);
//        glLoadIdentity();
//        glViewport(0,0, width, height);
//
//        gluPerspective(45.0, width/height, 0.1, 1000.0);
//
//        displayCB();
    }


    /**
     *
     * @param argc
     * @param args
     */
    public static void main(String[] args) {
        
        
        WinGL.create(WIN_XPOS, WIN_YPOS, WIN_XRES, WIN_YRES);
        SceneGL = new glScene(WinGL);
        SceneGL.draw();
        
    }
}
