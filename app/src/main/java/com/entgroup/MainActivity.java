package com.entgroup;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.libfifo.FifoController;

import java.nio.charset.StandardCharsets;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    /*static {
        System.loadLibrary("fifo-v7a");
    }*/

    String url = "/////gcEBgAGAwMEBAEHBAZjfCZvbWBsJT4ldnNpdz4oK3doZn0pfm9laWN+cSlwcStrbXFhKH5+WzYwMzY0NTExPzA0NjI7ZnFzbFhvYn06NTI2NDYyMzc8Mik1Mj49MTE1Nyo0KjJiPWQyMDxiMmU0MjRiZ2M0YjE3YWViYzw+YTYzMTBkJismaHZuY25qJT4ldnNpdz4oK3doZn0pfm9laWN+cSlwcStrbXFhKH5+WzYwMzY0NTExPzA0NjI7ZnFzbFhvYn06NTI2NDYyMzc8Mik+NT80MjQ+NCo0KjMwNmMzNzIyYWU2ZDE2NGY9YjxmMTc0YzExYDM2YTJmJismamFjbXJpJT4ldnNpdz4oK3doZn0pfm9laWN+cSlwcStrbXFhKH5+WzYwMzY0NTExPzA0NjI7ZnFzbFhvYn06NTI2NDYyMzc8MikwNjEwNzUxPSo0KjEyN2Q1Yjw3MDM3YTIyPGRiNmYxPDI1MGJmYTY3YWBmJno=";

    String temp = "/////gAEBQABAwMEBwAEAAFoYWxobw==";

    String test = "d29zaGl5aWdlY2hlbmd4dXl1YW4=";

    String aaa = "/////gEC//0EAAD/+v4DB/sGAfoEAAYB/fz6/fwE/QX7AAL++/7+Bf/6/PsEBQYB+vn8BAP7/wAA/gAAAv4DBQUEAP8A/fkEBv8F+/sFBgf+Af38+wEAAP37BQX5AAX+BAQG/P/6BwQEAAUFB/0C+wb9/AP8BfwA+gUBAwQBAAAFBf4D/v8HAPkB+wUHBf8DAQcA/fwHB//6AAP8/PwDAv//BQYG/v39Av4G/P0A/AT8+Qb9/QD8/vwA+QL9/Ab5Agf6AfwH/wf6BwABBPsHBwQGAgf8BAUCAwYFBAIHAPkD+wP+/QAHAQP++gb/+QX9Agb6A/kABQD8/gQCBf0G/QYD//wG+f8BAgEGdm1yavn8B/r7B/8BAwD++wD+/wP8BvoDAPkF/PwBBwMFAgT/+QED+wT/+wAB+fwF+vkBAf4BB/wFBAb5/QUHBvoE/P4F/AAEB/r8/P/7/PkEAAP6BAMH/f/5+v8DBAL8/wAGAf7+AAMD+QAHAAT++vwAAwAE/vsABgYGAP0CBgf7AAED+//8Bfr8Af4A/wcF/P4F/AAF+/8C/AIGB/7+AP36B//+AAQE/AIHBAP6AAAGAPoBBP/9BP39AP/5/fn/BAf7AgUC/gAHBQQE/AEG/QQD/QACAAT+/AT++gH6BAP7+QT9A/n9/AL7Bv8F+wEEAgX9/PwAAPr7/P7+AAQHBv4=";

    String b = "/////gACAQcGAAIDPnsgb3BpZWlsX2RsdCI4Imp0dnA4Ly1wbmF7Lmdudmdwb3dwLGNtbS1sa3ZnL3h5XTE2MjA5MTM0ODoyOjgsZm52PWF3dGpfaWV7PTM1MDQzMjc2NDYvMTY1MDczOTEtMi1hOWMzYWM7YTE1MmZjNmE2NGU0Mjc4YDIzODEyMjkyYiR1a2Q/entfMzQwMjszMTY6ODA4OiIuImppZWggOiBodnRyOi0vcmxjeSxlbHRlcm11ci5hb28vbml0ZS16e18zNDAyOzMxNjo4MDg6LmRsdD9jdXZoXWtneT8xNzI2MTA1NDY0LTY2MTE7NTYwLzAvMDNhZzk6Y2cyOjQzMDphZDU2NWBiMGZjZWY5NWI0MGQiLiJqaWVoXWZudiA6IGh2dHI6LS9ybGN5LGVsdGVybXVyLmFvby9uaXRlLXp7XzM0MDI7MzE2OjgwODouZGx0P2N1dmhda2d5PzE3MjYxMDU0NjQtMzQ3MjUxOzMvMC9jO2ExY2E5YzM3MGRhNGM0Nmc2MDU6YjAxOjMwMDswYCZ3aWY9eHldMTYyMDkxMzQ4OjI6OCAsIG9waWVpbCI4Imp0dnA4Ly1wbmF7Lmdudmdwb3dwLGNtbS1sa3ZnL3h5XTE2MjA5MTM0ODoyOjgsZm52PWF3dGpfaWV7PTM1MDQzMjc2NDYvNDsxMTExNDctMi1mZGM5ZzVhMDFlZmM2MTM2NWRnMjMxNDAxMDtkNmRhNCAsIG1nZGt1b19kbHQiOCJqdHZwOC8tcG5hey5nbnZncG93cCxjbW0tbGt2Zy94eV0xNjIwOTEzNDg6Mjo4LGZudj1hd3RqX2llez0zNTA0MzI3NjQ2LzE2NTA3MzkxLTItYTljM2FjO2ExNTJmYzZhNjRlNDI3OGAyMzgxMjI5MmIkdWtkP3p7XzM0MDI7MzE2OjgwODoiLiJvZWZpd20gOiBodnRyOi0vcmxjeSxlbHRlcm11ci5hb28vbml0ZS16e18zNDAyOzMxNjo4MDg6LmRsdD9jdXZoXWtneT8xNzI2MTA1NDY0LTUxMTI2OTcwLzAvNTI5YzE6YWM2O2JnMWQ1MjlgNzMxZmNgOTIwOjdgODEifwcHBQcEAAY=";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        GlobalConfig.instance().init(this);

        FifoController.getKey(GlobalConfig.instance().getApplicationContext());

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);

        String string = FifoController.decryptVipPlayInfo(b);

        tv.setText(string);

        FifoController.closeFifo();
    }
}
