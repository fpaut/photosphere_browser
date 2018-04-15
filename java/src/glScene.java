
import glModels.glAxes;
import glModels.glQuad;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author user
 */
class glScene {

    private final glAxes  axes = new glAxes();
    private final glQuad  quad = new glQuad();
    private final glWin   winGL;
    glScene(glWin WinGL) {
        winGL = WinGL;
    }
       
    public void draw() {
        // Adding Axes to the GL scene
         winGL.addGlModel(axes.getClass());
        // Adding a quad to the GL scene
         winGL.addGlModel(quad.getClass());
    }
    
}
