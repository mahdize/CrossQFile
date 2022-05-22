package crossqfile;

import android.app.Activity;
import android.os.Bundle;
import android.content.Intent;
import android.util.Log;

import org.qtproject.qt5.android.bindings.QtActivity;

public class MainActivity extends QtActivity {

    public static final int REQUEST_CODE_SELECT_FILE_URI =1;
    public static String selectedUriString = "";
    public static native void stopWaiting();

    private static Activity staticInstance;

    public void onCreate(Bundle bundle){
        super.onCreate(bundle);
        staticInstance = this;
    }

    public void onActivityResult(int requestCode, int resultCode, Intent resultData){
        super.onActivityResult(requestCode, resultCode, resultData);
        selectedUriString = "";
        try {
            if (resultCode == Activity.RESULT_OK) {
                if (requestCode == REQUEST_CODE_SELECT_FILE_URI) {
                        selectedUriString = resultData.getData().toString();
                }
            }
        }catch (Exception e){
            Log.e("Exception","Caught Exception in MainActivity.onActivityResult method", e);
        }
        stopWaiting();
    }
    
    public static void selectFile(){
        try{
            Intent intent = new Intent(Intent.ACTION_OPEN_DOCUMENT);
            intent.addCategory(Intent.CATEGORY_OPENABLE);
            intent.setType("*/*");
            staticInstance.startActivityForResult(intent, REQUEST_CODE_SELECT_FILE_URI);
        }
        catch (Exception e){
            Log.e("Exception","Caught Exception in MainActivity.selectFile method", e);
            stopWaiting();
        }
    }
    
    public static String getSelectedUri(){
        if(selectedUriString!=null) {
            return selectedUriString;
        }else{
            return "";
        }
    }
}
