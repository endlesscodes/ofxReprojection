#pragma once

#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "ofMain.h"
#include "ofxBase3DVideo.h"
#include "ofxReprojectionCalibrationData.h"
#include "ofxReprojectionCalibrationConfig.h"

#include "ofxGLFWWindow.h"

// 
// This class takes care of the calibration of depth cam and projector.
//
// The constructor takes a ofxBase3DVideo object which supplies the depth cam images
// and a window onto which the projector output is drawn. This window should be a fullscreen
// window on the projector.
//


class ofxReprojectionCalibration {
public:
	ofxReprojectionCalibration();
	~ofxReprojectionCalibration();

	bool init(  	ofxBase3DVideo *cam, 
			ofxGLFWWindow *projector_win, 
			ofxReprojectionCalibrationConfig config = ofxReprojectionCalibrationConfig());
	void update();

	void finalize();

	void drawCalibrationStatusScreen();

	bool loadData(string filename);

	static ofxReprojectionCalibrationData loadDataFromFile(string filename) {
		return ofxReprojectionCalibrationData::loadFromFile(filename);
	}
	static void saveDataToFile(ofxReprojectionCalibrationData data, string filename);
	static ofMatrix4x4 calculateReprojectionTransform(ofxReprojectionCalibrationData data);

	void reset();
	void deleteLastMeasurement();

	static void makechessboard(uchar* pixels, int img_width, int img_height, int rows, int cols, int x, int y, int width, int height, char brightness);
	static const cv::Mat lm_affinerow;
	static void lm_evaluate_camera_matrix(const double *par, int m_dat, const void *data, double *fvec, int *info);

private:
	ofxBase3DVideo* cam;
	ofxReprojectionCalibrationData *data;
	ofxReprojectionCalibrationConfig config;

	int stability_buffer_i;
	int cam_w, cam_h;
	int projector_w, projector_h;

	ofxGLFWWindow *projector_win;

	bool chessfound;
	bool chessfound_includes_depth;
	bool chessfound_planar;
	bool chessfound_enough_frames;
	bool chessfound_variance_ok;

	
	int chess_rows;
	int chess_cols;
	int chess_x;
	int chess_y;
	int chess_width;
	int chess_height;
	int chess_brightness;

	vector< vector<cv::Point3f> > corner_history;



	bool measurement_pause;
	unsigned long measurement_pause_time;

	double plane_r2;
	uint num_ok_frames;
	float largest_variance_xy;
	float largest_variance_z;


};

