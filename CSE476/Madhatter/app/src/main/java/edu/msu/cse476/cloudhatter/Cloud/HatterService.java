package edu.msu.cse476.cloudhatter.Cloud;

import android.graphics.Canvas;

import edu.msu.cse476.cloudhatter.Cloud.Models.Catalog;
import edu.msu.cse476.cloudhatter.Cloud.Models.DeleteResult;
import edu.msu.cse476.cloudhatter.Cloud.Models.LoadResult;
import edu.msu.cse476.cloudhatter.Cloud.Models.SaveResult;
import edu.msu.cse476.cloudhatter.SaveDlg;
import retrofit2.Call;
import retrofit2.http.DELETE;
import retrofit2.http.Field;
import retrofit2.http.FormUrlEncoded;
import retrofit2.http.GET;
import retrofit2.http.POST;
import retrofit2.http.Query;

import static edu.msu.cse476.cloudhatter.Cloud.Cloud.CATALOG_PATH;
import static edu.msu.cse476.cloudhatter.Cloud.Cloud.LOAD_PATH;
import static edu.msu.cse476.cloudhatter.Cloud.Cloud.SAVE_PATH;
import static edu.msu.cse476.cloudhatter.Cloud.Cloud.DELETE_PATH;

public interface HatterService {
    @GET(CATALOG_PATH)
    Call<Catalog> getCatalog(
            @Query("user") String userId,
            @Query("magic") String magic,
            @Query("pw") String password
    );

    @GET(LOAD_PATH)
    Call<LoadResult> loadHat(
            @Query("user") String userId,
            @Query("magic") String magic,
            @Query("pw") String password,
            @Query("id") String idHatToLoad
    );

    @FormUrlEncoded
    @POST(SAVE_PATH)
    Call<SaveResult> saveHat(@Field("xml") String xmlData);

    @GET(DELETE_PATH)
    Call<DeleteResult> deleteHat(
            @Query("user") String userId,
            @Query("magic") String magic,
            @Query("pw") String password,
            @Query("id") String idHatToDelete
    );
}
