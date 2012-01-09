// created date : 2011/10/29 23:48:22
// last updated : 2011/12/30 00:06:14
// Java3D サンプル
// http://www.maroon.dti.ne.jp/koten-kairo/works/Java3D/install2.html

import javax.media.j3d.*;
import javax.vecmath.*;
import com.sun.j3d.utils.universe.*;
import com.sun.j3d.utils.geometry.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import java.util.*;
import java.util.Timer;

public class Java3D_Sample{
	//仮想空間全体
	SimpleUniverse universe;

	//オブジェクトのためのグループ
	BranchGroup group1;
	//オブジェクトの座標変換のためのグループ
	TransformGroup transform_group1;
	//オブジェクトの座標変換のためのクラス
	Transform3D transform1;
	float rot_value; //回転角を管理

	public static void main(String[] args){
		Java3D_Sample test = new Java3D_Sample();
	}

	//=============================================================================
	//コンストラクタ
	public Java3D_Sample(){
		///まずは、基礎フレームの設定。
		JFrame frame = new JFrame();
		frame.setSize(250,250);
		frame.setTitle("Java3D　動作確認");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		JPanel cp = new JPanel();
		cp.setLayout(null);
		frame.add(cp);


		///次にJava3D関係の設定。
		//現在使用している画面の、ハードウェア情報を取得する
		GraphicsConfiguration g_config = SimpleUniverse.getPreferredConfiguration();
		//Canvas3Dというのが、3Dグラフィクスを表示する領域となる
		Canvas3D canvas = new Canvas3D(g_config);
		//3D表示領域の大きさを設定。今回はウィンドウいっぱいに表示する
		canvas.setBounds(0,0,250,250);
		//コンテントペインにCanvas3Dを登録
		cp.add(canvas);

		///3D空間を構築していきます
		//仮想空間のインスタンスを生成。表示先としてcanvasを指定。
		universe = new SimpleUniverse(canvas);
		//オブジェクトの「枝」を１つ作る
		group1 = new BranchGroup();
 
		//「カラーキューブ」を１つ生成
		ColorCube cube = new ColorCube(0.4f);
		//座標変換クラスを生成
		transform_group1 = new TransformGroup();
		//座標変換の書き換えを許可
		transform_group1.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
		//カラーキューブを座標変換クラスに登録
		transform_group1.addChild(cube);
		//座標変換内容
		transform1 = new Transform3D();
		//「枝」に座標変換クラスを登録
		group1.addChild(transform_group1);
		//仮想空間に「枝」を登録（これは最後に・・・！）
		universe.addBranchGraph(group1);
		//回転数をリセット
		rot_value=0.0f;
  
		///視点について設定
		//視点についてのハードウェア情報を取得。  
		ViewingPlatform vp = universe.getViewingPlatform();
		//視点のための座標変換クラスを用意
		TransformGroup Camera = vp.getViewPlatformTransform();
		//カメラの位置ベクトル
		Transform3D view_pos = new Transform3D();
		//カメラの位置を決める
		Vector3f pos_vec = new Vector3f(1.4f,1.4f,1.4f);
		//カメラの位置について、座標変換実行
		view_pos.setTranslation(pos_vec);

		//カメラの向きを示すベクトル
		Transform3D view_dir = new Transform3D();
		Transform3D view_dir2 = new Transform3D();

		//カメラの向きを決める
		view_dir.rotY(Math.PI/4);
		view_dir2.rotX(-Math.PI/4 + 0.1f);
		view_dir.mul(view_dir2);
 
		//カメラの位置およびカメラの向きを統合 
		view_pos.mul(view_dir);
  
		//カメラの位置情報を登録
		Camera.setTransform(view_pos);


		///回転のためのタイマーを設定
		Timer timer = new Timer();
		timer.schedule(new cube_rot(),0,40);
  
		//ウィンドウを可視化
		frame.setVisible(true);
	}
	
	
	//=============================================================================
	//内部クラスとして、タイマー割り込み（？）を記述
	class cube_rot extends TimerTask{
		public void run(){
			rot_value += Math.PI/60; //回転角を増やす
			transform1.rotY(rot_value); //回転の座標変換実行
			transform_group1.setTransform(transform1); //座標変換を登録
			
			//１回転したら、回転角をリセットしておく
			if(rot_value>Math.PI*2) rot_value=0.0f;
		}
	}
}
