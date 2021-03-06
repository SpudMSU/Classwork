package edu.msu.cassett8.checkers;

import android.app.AlertDialog;
import android.content.Context;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.graphics.RectF;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;

import java.util.ArrayList;

import static java.lang.String.valueOf;

public class CheckerBoard {

    boolean initialized = false;
    final static float SCALE_IN_VIEW = .95f;

    private boolean went = false;
    int formerID = -1;
    private int puzzleSize;
    private int marginX;
    private int marginY;
    private float scaleFactor;
    private View mCheckersView;
    private String playerOne;
    private String playerTwo;
    private boolean isEnd= false;
    private int winner = 1;
    private boolean popupShown = false;
    private int turn = 1;
    private boolean selected = false;
    private CheckerPiece jumpedPiece;
    private float touchedPieceX;
    private float touchedPieceY;
    private float touchedPieceWidth;
    private float touchedPieceHeight;


    Context mContext;
    public float leftEdge = 0.07f;
    public float rightEdge = 0.9f;
    public float diff = 0.05f;
    public float topEdge = 0.07f;
    public float bottomEdge = 0.9f;

    private ArrayList<WhiteChecker> whitePieces = new ArrayList<WhiteChecker>();
    private ArrayList<GreenChecker> greenPieces = new ArrayList<GreenChecker>();
    /**
     * Available moves for the current piece
     */
    private ArrayList<AvailableMove> availableMoves = new ArrayList<AvailableMove>();

    private final String White_Location="WhiteChecker.locations";
    private final String Green_Location="GreenChecker.locations";
    private final String Green_IDs="GreenChecker.ids";
    private final String White_IDs="WhiteChecker.ids";
    /**
     * Save the puzzle to a bundle
     * @param bundle The bundle we save to
     */
    public void saveInstanceState(Bundle bundle) {

        float [] wlocations = new float[whitePieces.size() * 2];
        int [] wids = new int[whitePieces.size() * 2];
        float [] glocations = new float[greenPieces.size() * 2];
        int [] gids = new int[greenPieces.size()* 2];
        float [] availLocs = new float[availableMoves.size()*2];
        float [] jumpedPLoc = new float[availableMoves.size()*2];
        int [] jumpedPid = new int[availableMoves.size()*2];
        int [] attachedPid = new int[availableMoves.size()*2];


        for(int i=0;  i<whitePieces.size(); i++) {
            CheckerPiece piece = whitePieces.get(i);
            wlocations[i*2] = piece.getX();
            wlocations[i*2+1] = piece.getY();
            wids[i*2] = piece.getID();
            wids[i*2+1] = piece.getKing() ? 1 : 0;
        }
        for(int i=0;  i<greenPieces.size(); i++) {
            CheckerPiece piece = greenPieces.get(i);
            glocations[i*2] = piece.getX();
            glocations[i*2+1] = piece.getY();
            gids[i*2] = piece.getID();
            gids[i*2+1] =  piece.getKing() ? 1 : 0;
        }
        for(int i=0; i< availableMoves.size(); i++)
        {
            AvailableMove m = availableMoves.get(i);
            CheckerPiece j = m.getJumpedPiece();
            CheckerPiece attached = m.getPiece();

            attachedPid[i*2] = attached.getID();
            availLocs[i*2] = m.getX();
            availLocs[i*2+1] = m.getY();
            if(j != null)
            {
                jumpedPid[i*2] = j.getID();
                jumpedPid[i*2+1] =  j.getKing() ? 1 : 0;
                jumpedPLoc[i*2] = j.getX();
                jumpedPLoc[i*2+1] = j.getY();
            }
            else {
                jumpedPid[i*2] = -1;
                jumpedPid[i*2+1] =  -1;
                jumpedPLoc[i*2] = -1;
                jumpedPLoc[i*2+1] = -1;
            }
        }

        bundle.putFloatArray(White_Location, wlocations);
        bundle.putIntArray(White_IDs,  wids);
        bundle.putFloatArray(Green_Location, glocations);
        bundle.putIntArray(Green_IDs,  gids);
        bundle.putFloatArray("availLoc", availLocs);
        bundle.putFloatArray("jloc", jumpedPLoc);
        bundle.putIntArray("jid", jumpedPid);
        bundle.putIntArray("attached", attachedPid);
        bundle.putInt("turn", turn);
        bundle.putInt("winner", winner);
        bundle.putBoolean("gameState", isEnd);
        bundle.putString("p1", playerOne);
        bundle.putString("p2", playerTwo);
        bundle.putBoolean("went", went);
        bundle.putString("former", valueOf(formerID));
        bundle.putFloat("touchedX",touchedPieceX);
        bundle.putFloat("touchedY",touchedPieceY);
        bundle.putFloat("touchedH",touchedPieceHeight);
        bundle.putFloat("touchedW",touchedPieceWidth);


        bundle.putBoolean("select", selected);


    }
    public int getWinner()
    {
        return winner;
    }
    public int getTurn()
    {
        return turn;
    }
    public void changeTurn()
    {
        if (turn == 1) { turn = 2;} else { turn = 1;}
        availableMoves = new ArrayList<AvailableMove>();
        jumpedPiece = null;
        formerID = -1;
        went = false;
        selected = false;
        mCheckersView.invalidate();

    }
    public boolean getisEnd()
    {
        return isEnd;
    }
    public void loadInstanceState(Bundle bundle, Context context) {

        if(bundle!=null) {
            String form = bundle.getString("former");
            if(form!=null)
            {
                formerID = Integer.parseInt(form);
            }
            selected = bundle.getBoolean("select");
            touchedPieceWidth = bundle.getFloat(("touchedW"));
            touchedPieceHeight = bundle.getFloat(("touchedH"));
            touchedPieceX = bundle.getFloat(("touchedX"));
            touchedPieceY = bundle.getFloat(("touchedY"));
            String temp = bundle.getString("p1");
            if(temp != null){ playerOne = temp;}
            temp = bundle.getString("p2");
            if(temp != null){ playerTwo = temp;}
            turn = bundle.getInt("turn");
            boolean went = bundle.getBoolean("went");
            if(went ==true)
            {
                this.went = went;
            }
            if(turn == 0) { turn = 1; }
            winner = bundle.getInt("winner");
            if(winner == 0) { winner = 1; }
            isEnd = bundle.getBoolean("gameState");
            float[] wlocations = bundle.getFloatArray(White_Location);
            int[] wids = bundle.getIntArray(White_IDs);
            float[] glocations = bundle.getFloatArray(Green_Location);
            int[] gids = bundle.getIntArray(Green_IDs);

            int[] tid = bundle.getIntArray("touchedID");
            float[] tlocations = bundle.getFloatArray("touchedPiece");

            float[] Jlocations = bundle.getFloatArray("jloc");
            float[] availLoc = bundle.getFloatArray("availLoc");
            int[] Jids = bundle.getIntArray("jid");
            int[] attachedID = bundle.getIntArray("attached");
            ArrayList<WhiteChecker> whitePieces = new ArrayList<WhiteChecker>();
            ArrayList<GreenChecker> greenPieces = new ArrayList<GreenChecker>();
            ArrayList<AvailableMove> moves = new ArrayList<AvailableMove>();


            if ((gids != null) && (wids !=null)) {
                for (int i = 0; i < (gids.length/2); i++) {

                    GreenChecker piece = new GreenChecker(context, gids[i*2]);
                    piece.SetKing(gids[i*2+1]);
                    piece.setCords(glocations[i * 2], glocations[i * 2 + 1]);
                    greenPieces.add(piece);
                }
                this.greenPieces = greenPieces;

                for (int i = 0; i < (wids.length/2); i++) {

                    WhiteChecker piece = new WhiteChecker(context, wids[i*2]);
                    piece.SetKing(wids[i*2+1]);
                    piece.setCords(wlocations[i * 2], wlocations[i * 2 + 1]);
                    whitePieces.add(piece);
                }
                this.whitePieces = whitePieces;

                initialized=true;
            }
            if(availLoc != null)
            {
                for (int i = 0; i < (availLoc.length/2); i++) {
                    CheckerPiece p = null;
                    int id = attachedID[i*2];
                    if(turn == 1){
                        for (GreenChecker j: greenPieces)
                        {
                            if(j.getID() == id)
                            {
                                p = j;
                            }
                        }
                    }
                    else {
                        for (WhiteChecker j: whitePieces)
                        {
                            if(j.getID() == id)
                            {
                                p = j;
                            }
                        }
                    }
                    CheckerPiece jumped = null;
                    if(Jids[i*2] !=-1)
                    {
                        jumped = new CheckerPiece(context, Jids[i*2]);
                        jumped.SetKing(Jids[i*2+1]);
                        jumped.setCords(Jlocations[i*2], Jlocations[i*2+1]);
                        jumpedPiece = jumped;
                    }

                    AvailableMove n = new AvailableMove(availLoc[i*2], availLoc[i*2+1], p, jumped);
                    moves.add(n);
                }
                availableMoves = moves;
            }


        }

    }






    /**
     * Completed puzzle bitmap
     */
    private Bitmap boardImage;

    private Paint outlinePaint;

    public CheckerBoard(Context context, View theView){
        mContext = context;
        mCheckersView = theView;
        boardImage = BitmapFactory.decodeResource(context.getResources(),
                R.drawable.checkersboard);


        //spawn white checkers
        for (int i=0; i<12; i++) {
            whitePieces.add(new WhiteChecker(context,
                    i));
        }

        //spawn green checkers
        for (int i=0; i<12; i++) {
            greenPieces.add(new GreenChecker(context,
                    i));

        }

    }

    public void draw(Canvas canvas) {

        int wid = canvas.getWidth();
        int hit = canvas.getHeight();

        if(!initialized)
        {
            setInitialPos();
            initialized=true;
        }

        // Determine the minimum of the two dimensions
        int minDim = wid < hit ? wid : hit;

        puzzleSize = (int)(minDim * SCALE_IN_VIEW);


        // Compute the margins so we center the puzzle
        marginX = (wid - puzzleSize) / 2;
        marginY = (hit - puzzleSize) / 2;

        //
        // Draw the outline of the puzzle
        //

        scaleFactor = (float)puzzleSize / (float)boardImage.getWidth();

        outlinePaint = new Paint(Paint.ANTI_ALIAS_FLAG);
        outlinePaint.setColor(0xFF504B);
        outlinePaint.setStyle(Paint.Style.STROKE);
        canvas.drawRect(marginX, marginY,
                marginX + puzzleSize, marginY + puzzleSize, outlinePaint);
        canvas.save();
        canvas.translate(marginX, marginY);
        canvas.scale(scaleFactor, scaleFactor);
        canvas.drawBitmap(boardImage, 0, 0, null);
        canvas.restore();

        if (selected) {
            canvas.save();
            // Convert x,y to pixels and add the margin, then draw
            canvas.translate(marginX + touchedPieceX * puzzleSize,
                    marginY + touchedPieceY * puzzleSize);

            // Scale it to the right size
            canvas.scale(scaleFactor/1.5f, scaleFactor/1.5f);

            // This magic code makes the center of the piece at 0, 0
            canvas.translate(touchedPieceWidth / 2f, -touchedPieceHeight / 2f);

            float squareSize = touchedPieceHeight;
            Paint linePaint = new Paint(Paint.ANTI_ALIAS_FLAG);
            linePaint.setColor(Color.YELLOW);
            linePaint.setStrokeWidth(3);

            canvas.drawRect(touchedPieceX -squareSize, touchedPieceY, touchedPieceX,
                    touchedPieceY +squareSize, linePaint);
            canvas.restore();

        }


        //draw all green checker pieces
        for(CheckerPiece piece : greenPieces) {
            piece.draw( canvas, marginX, marginY, puzzleSize, scaleFactor);
        }

        //draw all white checker pieces
        for(CheckerPiece piece : whitePieces) {
            piece.draw( canvas, marginX, marginY, puzzleSize, scaleFactor);
        }

        /**
         * TODO: Add loop to draw all available moves at end of draw
         */
        for (AvailableMove space : availableMoves){
            space.draw(canvas, marginX, marginY, puzzleSize, scaleFactor);
        }


    }

    public boolean onTouchEvent(View view, MotionEvent event) {

        if (isEnd)
        {
            return false;
        }

        float relX = (event.getX() - marginX) / puzzleSize;
        float relY = (event.getY() - marginY) / puzzleSize;
        switch (event.getActionMasked()) {

            case MotionEvent.ACTION_DOWN:
                boolean result = onTouched(relX, relY, view);
                if(isEnd)
                {
                    if(!popupShown)
                    {
                        // The puzzle is done
                        // Instantiate a dialog box builder
                        AlertDialog.Builder builder =
                                new AlertDialog.Builder(view.getContext());

                        // Parameterize the builder

                        builder.setTitle(R.string.endGame);
                        int id = 0;
                        Resources res = mContext.getResources();
                        String player;
                        if(winner==1){player=playerOne;}else {player=playerTwo;}
                        String msg = player + " " + res.getString(R.string.player1Win);
                        builder.setMessage(msg);
                        builder.setPositiveButton(android.R.string.ok, null);

                        // Create the dialog box and show it
                        AlertDialog alertDialog = builder.create();
                        alertDialog.show();
                        popupShown=true;
                    }
                }
                return result;
        }
        return false;
    }
    private boolean onTouched(float x, float y, View view) {

        // Check each piece to see if it has been hit
        // We do this in reverse order so we find the pieces in front

        if(turn == 2) {


            for (int p = whitePieces.size() - 1; p >= 0; p--) {
                if(went){
                    if(p==formerID && jumpedPiece !=null)
                    {
                        if (whitePieces.get(p).hit(x, y, puzzleSize, scaleFactor)) {
                            // We hit a piece!
                            findDoubles(whitePieces.get(p), 0);
                            setTouchedPiece(whitePieces.get(p));
                            selected = true;
                            formerID=-1;
                            return true;
                        }
                    }
                }
                else {
                    if (whitePieces.get(p).hit(x, y, puzzleSize, scaleFactor)) {
                        // We hit a piece!
                        findAvailableMoves(whitePieces.get(p), 0);
                        setTouchedPiece(whitePieces.get(p));
                        selected = true;
                        if(jumpedPiece!=null) {
                            formerID = p;
                        }
                        return true;
                    }
                }
            }
        }

        else {

            for (int p = greenPieces.size() - 1; p >= 0; p--) {
                if(went){
                    if(p==formerID && jumpedPiece != null)
                    {
                        if (greenPieces.get(p).hit(x, y, puzzleSize, scaleFactor)) {
                            // We hit a piece!
                            findDoubles(greenPieces.get(p), 1);
                            setTouchedPiece(greenPieces.get(p));
                            selected = true;
                            formerID = -1;
                            return true;
                        }
                    }
                }
                else {
                    if (greenPieces.get(p).hit(x, y, puzzleSize, scaleFactor)) {
                        // We hit a piece!
                        findAvailableMoves(greenPieces.get(p), 1);
                        setTouchedPiece(greenPieces.get(p));
                        selected = true;
                        if(jumpedPiece!=null) {
                            formerID = p;
                        }
                        return true;
                    }
                }
            }
        }
        if(!availableMoves.isEmpty()) {
            for (int p = availableMoves.size() - 1; p >= 0; p--) {
                if (availableMoves.get(p).hit(x, y, puzzleSize, scaleFactor)) {
                    // We hit a piece!
                    selected = false;
                    AvailableMove i = availableMoves.get(p);

                    //Check if it is king
                    CheckerPiece c = availableMoves.get(p).getPiece();
                    //Check if it is green
                    if (isGreen(c.getX(), c.getY())) {
                        //Then check if it is on the edges
                        if (isTop(c.getY())) {
                            c.isKingPiece();
                        }

                    }
                    //Check if it is white
                    if (isWhite(c.getX(), c.getY())) {
                        //Then check if it is on the edges
                        if (isBottom(c.getY())) {
                            c.isKingPiece();
                        }
                    }


                    CheckerPiece jumped = i.getJumpedPiece();

                    if (jumped != null) {
                        if (turn == 1) {
                            for (int j = whitePieces.size() - 1; j >= 0; j--) {
                                if (whitePieces.get(j).equals(jumped)) {
                                    whitePieces.remove(j);
                                    if (whitePieces.isEmpty()) {
                                        isEnd = true;
                                        winner = 1;
                                    }
                                    break;
                                }
                            }
                        } else if (turn == 2) {
                            for (int j = greenPieces.size() - 1; j >= 0; j--) {
                                if (greenPieces.get(j).equals(jumped)) {
                                    greenPieces.remove(j);
                                    if (greenPieces.isEmpty()) {
                                        isEnd = true;
                                        winner = 2;
                                    }
                                    break;
                                }
                            }
                        }
                    }
                    for (p = availableMoves.size() - 1; p >= 0; p--) {
                        availableMoves.remove(p);
                    }

                    if (went) {
                        formerID = -1;
                    }
                    went = true;
                    mCheckersView.invalidate();
                    return true;

                }
            }
        }
        if(selected)
        {
            AlertDialog.Builder builder =
                    new AlertDialog.Builder(view.getContext());

            // Parameterize the builder

            builder.setTitle(R.string.invalid);
            Resources res = mContext.getResources();
            builder.setMessage(R.string.invalidMsg);
            builder.setPositiveButton(android.R.string.ok, null);

            // Create the dialog box and show it
            AlertDialog alertDialog = builder.create();
            alertDialog.show();
        }
        return false;

    }
    public void setTouchedPiece(CheckerPiece piece) {
        touchedPieceX = piece.getX();
        touchedPieceY = piece.getY();
        touchedPieceHeight = piece.getHeight();
        touchedPieceWidth = piece.getWidth();
    }

    public boolean isLeftEdge(float x) {
        if(Math.abs(leftEdge - x ) < diff)
        {
            return true;
        }

        return false;
    }
    public boolean isRightEdge(float x) {
        if(Math.abs(rightEdge - x) < diff)
        {
            return true;
        }

        return false;
    }
    public boolean isTop(float y) {
        if (Math.abs(topEdge - y) < diff) {
            return true;
        }
        return false;
    }

    public boolean isBottom(float y) {
        if (Math.abs(bottomEdge - y) < diff) {
            return true;
        }
        return false;
    }


    private boolean isJumpable(float x, float y, int type) {
        if (type == 1) {
            for (int p = whitePieces.size() - 1; p >= 0; p--) {
                if (whitePieces.get(p).hit(x, y, puzzleSize, scaleFactor)) {
                    // We hit a piece!
                    if (!isRightEdge(whitePieces.get(p).getX()) && !isLeftEdge(whitePieces.get(p).getX()) ) {
                        jumpedPiece = whitePieces.get(p);
                        return true;
                    }
                }
            }
        }
        if (type == 0) {
            for (int p = greenPieces.size() - 1; p >= 0; p--) {
                if (greenPieces.get(p).hit(x, y, puzzleSize, scaleFactor)) {
                    // We hit a piece!
                    if (!isRightEdge(greenPieces.get(p).getX()) && !isLeftEdge(greenPieces.get(p).getX()) ) {
                        jumpedPiece = greenPieces.get(p);
                        return true;
                    }
                }
            }
        }
        return false;
    }
    private boolean isWhite(float x, float y) {
        for (int p = whitePieces.size() - 1; p >= 0; p--) {
            if (whitePieces.get(p).hit(x, y, puzzleSize, scaleFactor)) {
                return true;
            }
        }
        return false;
    }

    private boolean isGreen(float x, float y) {
        for (int p = greenPieces.size() - 1; p >= 0; p--) {
            if (greenPieces.get(p).hit(x, y, puzzleSize, scaleFactor)) {
                return true;
            }
        }
        return false;
    }

    public void findAvailableMoves(CheckerPiece piece , int type) {
        availableMoves.clear();
        if (type == 0) {

            if (piece.getKing()) {
                if (isJumpable(piece.getX() + .125f, piece.getY() + .125f, type)) {
                    availableMoves.add(new AvailableMove(piece.getX() + .25f, piece.getY() + .25f, piece, jumpedPiece));
                }
                if (isJumpable(piece.getX() - .125f, piece.getY() + .125f, type)) {
                    availableMoves.add(new AvailableMove(piece.getX() - .25f, piece.getY() + .25f, piece, jumpedPiece));
                }
                if (isJumpable(piece.getX() - .125f, piece.getY() - .125f, type)) {
                    availableMoves.add(new AvailableMove(piece.getX() - .25f, piece.getY() - .25f, piece, jumpedPiece));
                }
                if (isJumpable(piece.getX() + .125f, piece.getY() - .125f, type)) {
                    availableMoves.add(new AvailableMove(piece.getX() + .25f, piece.getY() - .25f, piece, jumpedPiece));
                }

                availableMoves.add(new AvailableMove(piece.getX() + .125f, piece.getY() + .125f, piece));
                availableMoves.add(new AvailableMove(piece.getX() - .125f, piece.getY() + .125f, piece));
                availableMoves.add(new AvailableMove(piece.getX() + .125f, piece.getY() - .125f, piece));
                availableMoves.add(new AvailableMove(piece.getX() - .125f, piece.getY() - .125f, piece));
            }
            else{
                if (isJumpable(piece.getX() + .125f, piece.getY() + .125f, type)) {
                    availableMoves.add(new AvailableMove(piece.getX() + .25f, piece.getY() + .25f, piece, jumpedPiece));
                }
                if (isJumpable(piece.getX() - .125f, piece.getY() + .125f, type)) {
                    availableMoves.add(new AvailableMove(piece.getX() - .25f, piece.getY() + .25f, piece, jumpedPiece));
                }
                availableMoves.add(new AvailableMove(piece.getX() + .125f, piece.getY() + .125f, piece));
                availableMoves.add(new AvailableMove(piece.getX() - .125f, piece.getY() + .125f, piece));
            }

        }

        if (type == 1) {
            if (piece.getKing()) {
                if (isJumpable(piece.getX() + .125f, piece.getY() + .125f, type)) {
                    availableMoves.add(new AvailableMove(piece.getX() + .25f, piece.getY() + .25f, piece, jumpedPiece));
                }
                if (isJumpable(piece.getX() - .125f, piece.getY() + .125f, type)) {
                    availableMoves.add(new AvailableMove(piece.getX() - .25f, piece.getY() + .25f, piece, jumpedPiece));
                }
                if (isJumpable(piece.getX() - .125f, piece.getY() - .125f, type)) {
                    availableMoves.add(new AvailableMove(piece.getX() - .25f, piece.getY() - .25f, piece, jumpedPiece));
                }
                if (isJumpable(piece.getX() + .125f, piece.getY() - .125f, type)) {
                    availableMoves.add(new AvailableMove(piece.getX() + .25f, piece.getY() - .25f, piece, jumpedPiece));
                }

                availableMoves.add(new AvailableMove(piece.getX() + .125f, piece.getY() + .125f, piece));
                availableMoves.add(new AvailableMove(piece.getX() - .125f, piece.getY() + .125f, piece));
            }
            else{
                if (isJumpable(piece.getX() - .125f, piece.getY() - .125f, type)) {
                    availableMoves.add(new AvailableMove(piece.getX() - .25f, piece.getY() - .25f, piece, jumpedPiece));
                }
                if (isJumpable(piece.getX() + .125f, piece.getY() - .125f, type)) {
                    availableMoves.add(new AvailableMove(piece.getX() + .25f, piece.getY() - .25f, piece, jumpedPiece));
                }
            }
            availableMoves.add(new AvailableMove(piece.getX() + .125f, piece.getY() - .125f, piece));
            availableMoves.add(new AvailableMove(piece.getX() - .125f, piece.getY() - .125f, piece));
        }
        for(int i =  availableMoves.size() - 1; i >= 0; i-- ) {
            AvailableMove move = availableMoves.get(i);
            if (isGreen(move.getX(),move.getY()) || (isWhite(move.getX(),move.getY())) || move.getX() < (leftEdge - .05f) ||
                    move.getX() > (rightEdge + .05f) || move.getY() < (topEdge - .05f)  || move.getY() > bottomEdge + .05f) {
                availableMoves.remove(i);
            }
        }
        mCheckersView.invalidate();
    }

    public void findDoubles(CheckerPiece piece , int type) {
        availableMoves.clear();
        if (type == 0) {

            if (piece.getKing()) {
                if (isJumpable(piece.getX() + .125f, piece.getY() + .125f, type)) {
                    availableMoves.add(new AvailableMove(piece.getX() + .25f, piece.getY() + .25f, piece, jumpedPiece));
                }
                if (isJumpable(piece.getX() - .125f, piece.getY() + .125f, type)) {
                    availableMoves.add(new AvailableMove(piece.getX() - .25f, piece.getY() + .25f, piece, jumpedPiece));
                }
                if (isJumpable(piece.getX() - .125f, piece.getY() - .125f, type)) {
                    availableMoves.add(new AvailableMove(piece.getX() - .25f, piece.getY() - .25f, piece, jumpedPiece));
                }
                if (isJumpable(piece.getX() + .125f, piece.getY() - .125f, type)) {
                    availableMoves.add(new AvailableMove(piece.getX() + .25f, piece.getY() - .25f, piece, jumpedPiece));
                }

            } else {
                if (isJumpable(piece.getX() + .125f, piece.getY() + .125f, type)) {
                    availableMoves.add(new AvailableMove(piece.getX() + .25f, piece.getY() + .25f, piece, jumpedPiece));
                }
                if (isJumpable(piece.getX() - .125f, piece.getY() + .125f, type)) {
                    availableMoves.add(new AvailableMove(piece.getX() - .25f, piece.getY() + .25f, piece, jumpedPiece));
                }
            }
        }
        else if (type == 1) {
            if (piece.getKing()) {
                if (isJumpable(piece.getX() + .125f, piece.getY() + .125f, type)) {
                    availableMoves.add(new AvailableMove(piece.getX() + .25f, piece.getY() + .25f, piece, jumpedPiece));
                }
                if (isJumpable(piece.getX() - .125f, piece.getY() + .125f, type)) {
                    availableMoves.add(new AvailableMove(piece.getX() - .25f, piece.getY() + .25f, piece, jumpedPiece));
                }
                if (isJumpable(piece.getX() - .125f, piece.getY() - .125f, type)) {
                    availableMoves.add(new AvailableMove(piece.getX() - .25f, piece.getY() - .25f, piece, jumpedPiece));
                }
                if (isJumpable(piece.getX() + .125f, piece.getY() - .125f, type)) {
                    availableMoves.add(new AvailableMove(piece.getX() + .25f, piece.getY() - .25f, piece, jumpedPiece));
                }

            }
            else{
                if (isJumpable(piece.getX() - .125f, piece.getY() - .125f, type)) {
                    availableMoves.add(new AvailableMove(piece.getX() - .25f, piece.getY() - .25f, piece, jumpedPiece));
                }
                if (isJumpable(piece.getX() + .125f, piece.getY() - .125f, type)) {
                    availableMoves.add(new AvailableMove(piece.getX() + .25f, piece.getY() - .25f, piece, jumpedPiece));
                }
            }
        }
        for(int i =  availableMoves.size() - 1; i >= 0; i-- ) {
            AvailableMove move = availableMoves.get(i);
            if (isGreen(move.getX(),move.getY()) || (isWhite(move.getX(),move.getY())) || move.getX() < (leftEdge - .05f) ||
                    move.getX() > (rightEdge + .05f) || move.getY() < (topEdge - .05f)  || move.getY() > bottomEdge + .05f) {
                availableMoves.remove(i);
            }
        }
        mCheckersView.invalidate();

    }
    public void setInitialPos()
    {
        //code for setting initial positions of checkers

        //first 12 are white and first 12 are green. May also be other way around. I dont know. x and y range from 0-.95f.

        //example of setting their locations (randomly)
        float whiteShift = 0;
        float greenShift = 0;
        int whiteCount = 0;
        int greenCount = 0;

        for(CheckerPiece piece : greenPieces) {
            if (greenCount <= 3) {
                piece.setCords((0.195f * SCALE_IN_VIEW) + greenShift, (0.987f * SCALE_IN_VIEW));
                greenShift = (greenShift + 0.25f);

            }
            if (greenCount == 4){
                greenShift = 0;
            }
            if (greenCount > 3 && greenCount <= 7){
                piece.setCords((0.065f * SCALE_IN_VIEW) + greenShift, (0.857f * SCALE_IN_VIEW));
                greenShift = (greenShift + 0.25f);

            }
            if (greenCount == 7){
                greenShift = 0;
            }
            if (greenCount > 7){
                piece.setCords((0.195f * SCALE_IN_VIEW) + greenShift, (0.725f * SCALE_IN_VIEW));
                greenShift = (greenShift + 0.25f);

            }
            greenCount++;
        }

        for(CheckerPiece piece : whitePieces) {

            if (whiteCount <= 3) {
                piece.setCords((0.065f * SCALE_IN_VIEW) + whiteShift, (0.065f * SCALE_IN_VIEW));
                whiteShift = (whiteShift + 0.25f);

            }
            if (whiteCount == 4){
                whiteShift = 0;
            }
            if (whiteCount > 3 && whiteCount <= 7){
                piece.setCords((0.195f * SCALE_IN_VIEW) + whiteShift, (0.195f * SCALE_IN_VIEW));
                whiteShift = (whiteShift + 0.25f);

            }
            if (whiteCount == 7){
                whiteShift = 0;
            }
            if (whiteCount > 7){
                piece.setCords((0.065f * SCALE_IN_VIEW) + whiteShift, (0.33f * SCALE_IN_VIEW));
                whiteShift = (whiteShift + 0.25f);

            }
            whiteCount++;

        }
    }

    public void setPlayerTwo(String playerTwo) {
        this.playerTwo = playerTwo;
    }

    public void setPlayerOne(String playerOne) {
        this.playerOne = playerOne;
    }
}
