// ----------------------------------------------------------------------------
// -                        Open3D: www.open3d.org                            -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2018-2021 www.open3d.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#include "open3d/data/Dataset.h"

#include "open3d/t/io/PointCloudIO.h"
#include "open3d/utility/FileSystem.h"
#include "open3d/utility/Helper.h"
#include "open3d/utility/Logging.h"
#include "tests/Tests.h"

namespace open3d {
namespace tests {

TEST(Dataset, DatasetBase) {
    // Prefix cannot be empty.
    data::Dataset ds("some_prefix");
    EXPECT_EQ(ds.GetDataRoot(),
              utility::filesystem::GetHomeDirectory() + "/open3d_data");

    data::Dataset ds_custom("some_prefix", "/my/custom/data_root");
    EXPECT_EQ(ds_custom.GetPrefix(), "some_prefix");
    EXPECT_EQ(ds_custom.GetDataRoot(), "/my/custom/data_root");
    EXPECT_EQ(ds_custom.GetDownloadDir(),
              "/my/custom/data_root/download/some_prefix");
    EXPECT_EQ(ds_custom.GetExtractDir(),
              "/my/custom/data_root/extract/some_prefix");
}

TEST(Dataset, SingleDownloadDataset) {
    const std::string prefix = "SingleDownloadDataset";
    const std::string data_root = utility::filesystem::GetHomeDirectory() +
                                  "/open3d_data/open3d_test";
    const std::string download_dir = data_root + "/download/" + prefix;
    const std::string extract_dir = data_root + "/extract/" + prefix;

    // Delete if files already exists.
    utility::filesystem::DeleteDirectory(data_root + "/download/" + prefix);
    utility::filesystem::DeleteDirectory(data_root + "/extract/" + prefix);

    const std::vector<std::string> url_mirrors = {
            "https://github.com/isl-org/open3d_downloads/releases/download/"
            "20220201-data/BunnyMesh.ply"};
    const std::string md5 = "568f871d1a221ba6627569f1e6f9a3f2";

    data::SingleDownloadDataset single_download_dataset(
            prefix, url_mirrors, md5,
            /*no_extact*/ true, data_root);

    // Check if file is downloaded and extracted / copied.
    EXPECT_TRUE(
            utility::filesystem::FileExists(download_dir + "/BunnyMesh.ply"));
    EXPECT_TRUE(
            utility::filesystem::FileExists(extract_dir + "/BunnyMesh.ply"));

    // Basic methods.
    EXPECT_EQ(single_download_dataset.GetPrefix(), prefix);
    EXPECT_EQ(single_download_dataset.GetDataRoot(), data_root);
    EXPECT_EQ(single_download_dataset.GetDownloadDir(), download_dir);
    EXPECT_EQ(single_download_dataset.GetExtractDir(), extract_dir);

    // Delete dataset.
    utility::filesystem::DeleteDirectory(download_dir);
    utility::filesystem::DeleteDirectory(extract_dir);
}

TEST(Dataset, DemoICPPointClouds) {
    const std::string prefix = "DemoICPPointClouds";
    const std::string data_root = utility::filesystem::GetHomeDirectory() +
                                  "/open3d_data/open3d_test";
    const std::string download_dir = data_root + "/download/" + prefix;
    const std::string extract_dir = data_root + "/extract/" + prefix;

    // Delete if files already exists.
    utility::filesystem::DeleteDirectory(data_root + "/download/" + prefix);
    utility::filesystem::DeleteDirectory(data_root + "/extract/" + prefix);

    data::DemoICPPointClouds demo_icp(data_root);
    // Check if downloaded.
    EXPECT_TRUE(utility::filesystem::DirectoryExists(download_dir));

    // Methods to get path.
    const std::vector<std::string> paths = {extract_dir + "/cloud_bin_0.pcd",
                                            extract_dir + "/cloud_bin_1.pcd",
                                            extract_dir + "/cloud_bin_2.pcd"};
    EXPECT_EQ(demo_icp.GetPaths(), paths);
    for (size_t i = 0; i < paths.size(); ++i) {
        EXPECT_EQ(demo_icp.GetPaths(i), paths[i]);
        // Check if the file actually exists.
        EXPECT_TRUE(utility::filesystem::FileExists(demo_icp.GetPaths(i)));
    }

    // Path to transformation log file.
    EXPECT_EQ(demo_icp.GetTransformationLogPath(), extract_dir + "/init.log");
    EXPECT_TRUE(utility::filesystem::FileExists(
            demo_icp.GetTransformationLogPath()));

    // Basic methods.
    EXPECT_EQ(demo_icp.GetPrefix(), prefix);
    EXPECT_EQ(demo_icp.GetDataRoot(), data_root);
    EXPECT_EQ(demo_icp.GetDownloadDir(), download_dir);
    EXPECT_EQ(demo_icp.GetExtractDir(), extract_dir);

    // Delete dataset.
    utility::filesystem::DeleteDirectory(download_dir);
    utility::filesystem::DeleteDirectory(extract_dir);
}

TEST(Dataset, DemoColoredICPPointClouds) {
    const std::string prefix = "DemoColoredICPPointClouds";
    const std::string data_root = utility::filesystem::GetHomeDirectory() +
                                  "/open3d_data/open3d_test";
    const std::string download_dir = data_root + "/download/" + prefix;
    const std::string extract_dir = data_root + "/extract/" + prefix;

    // Delete if files already exists.
    utility::filesystem::DeleteDirectory(data_root + "/download/" + prefix);
    utility::filesystem::DeleteDirectory(data_root + "/extract/" + prefix);

    data::DemoColoredICPPointClouds demo_cicp(data_root);
    // Check if downloaded.
    EXPECT_TRUE(utility::filesystem::DirectoryExists(download_dir));

    // Methods to get path.
    const std::vector<std::string> paths = {extract_dir + "/frag_115.ply",
                                            extract_dir + "/frag_116.ply"};
    EXPECT_EQ(demo_cicp.GetPaths(), paths);
    for (size_t i = 0; i < paths.size(); ++i) {
        EXPECT_EQ(demo_cicp.GetPaths(i), paths[i]);
        // Check if the file actually exists.
        EXPECT_TRUE(utility::filesystem::FileExists(demo_cicp.GetPaths(i)));
    }

    // Basic methods.
    EXPECT_EQ(demo_cicp.GetPrefix(), prefix);
    EXPECT_EQ(demo_cicp.GetDataRoot(), data_root);
    EXPECT_EQ(demo_cicp.GetDownloadDir(), download_dir);
    EXPECT_EQ(demo_cicp.GetExtractDir(), extract_dir);

    // Delete dataset.
    utility::filesystem::DeleteDirectory(download_dir);
    utility::filesystem::DeleteDirectory(extract_dir);
}

TEST(Dataset, DemoCropPointCloud) {
    const std::string prefix = "DemoCropPointCloud";
    const std::string data_root = utility::filesystem::GetHomeDirectory() +
                                  "/open3d_data/open3d_test";
    const std::string download_dir = data_root + "/download/" + prefix;
    const std::string extract_dir = data_root + "/extract/" + prefix;

    // Delete if files already exists.
    utility::filesystem::DeleteDirectory(data_root + "/download/" + prefix);
    utility::filesystem::DeleteDirectory(data_root + "/extract/" + prefix);

    data::DemoCropPointCloud demo_crop_pcd(data_root);
    // Check if downloaded.
    EXPECT_TRUE(utility::filesystem::DirectoryExists(download_dir));

    // Methods to get path.
    EXPECT_EQ(demo_crop_pcd.GetPointCloudPath(), extract_dir + "/fragment.ply");
    EXPECT_TRUE(
            utility::filesystem::FileExists(demo_crop_pcd.GetPointCloudPath()));
    EXPECT_EQ(demo_crop_pcd.GetCroppedJSONPath(),
              extract_dir + "/cropped.json");
    EXPECT_TRUE(utility::filesystem::FileExists(
            demo_crop_pcd.GetCroppedJSONPath()));

    // Basic methods.
    EXPECT_EQ(demo_crop_pcd.GetPrefix(), prefix);
    EXPECT_EQ(demo_crop_pcd.GetDataRoot(), data_root);
    EXPECT_EQ(demo_crop_pcd.GetDownloadDir(), download_dir);
    EXPECT_EQ(demo_crop_pcd.GetExtractDir(), extract_dir);

    // Delete dataset.
    utility::filesystem::DeleteDirectory(download_dir);
    utility::filesystem::DeleteDirectory(extract_dir);
}

TEST(Dataset, DemoFeatureMatchingPointClouds) {
    const std::string prefix = "DemoFeatureMatchingPointClouds";
    const std::string data_root = utility::filesystem::GetHomeDirectory() +
                                  "/open3d_data/open3d_test";
    const std::string download_dir = data_root + "/download/" + prefix;
    const std::string extract_dir = data_root + "/extract/" + prefix;

    // Delete if files already exists.
    utility::filesystem::DeleteDirectory(data_root + "/download/" + prefix);
    utility::filesystem::DeleteDirectory(data_root + "/extract/" + prefix);

    data::DemoFeatureMatchingPointClouds demo_feature_matching(data_root);
    // Check if downloaded.
    EXPECT_TRUE(utility::filesystem::DirectoryExists(download_dir));

    // Methods to get path.
    const std::vector<std::string> point_cloud_paths = {
            extract_dir + "/cloud_bin_0.pcd", extract_dir + "/cloud_bin_1.pcd"};
    EXPECT_EQ(demo_feature_matching.GetPointCloudPaths(), point_cloud_paths);

    const std::vector<std::string> fpfh_feature_paths = {
            extract_dir + "/cloud_bin_0.fpfh.bin",
            extract_dir + "/cloud_bin_1.fpfh.bin"};
    EXPECT_EQ(demo_feature_matching.GetFPFHFeaturePaths(), fpfh_feature_paths);

    const std::vector<std::string> l32d_feature_paths = {
            extract_dir + "/cloud_bin_0.d32.bin",
            extract_dir + "/cloud_bin_1.d32.bin"};
    EXPECT_EQ(demo_feature_matching.GetL32DFeaturePaths(), l32d_feature_paths);

    // Basic methods.
    EXPECT_EQ(demo_feature_matching.GetPrefix(), prefix);
    EXPECT_EQ(demo_feature_matching.GetDataRoot(), data_root);
    EXPECT_EQ(demo_feature_matching.GetDownloadDir(), download_dir);
    EXPECT_EQ(demo_feature_matching.GetExtractDir(), extract_dir);

    // Delete dataset.
    utility::filesystem::DeleteDirectory(download_dir);
    utility::filesystem::DeleteDirectory(extract_dir);
}

TEST(Dataset, DemoPoseGraphOptimization) {
    const std::string prefix = "DemoPoseGraphOptimization";
    const std::string data_root = utility::filesystem::GetHomeDirectory() +
                                  "/open3d_data/open3d_test";
    const std::string download_dir = data_root + "/download/" + prefix;
    const std::string extract_dir = data_root + "/extract/" + prefix;

    // Delete if files already exists.
    utility::filesystem::DeleteDirectory(data_root + "/download/" + prefix);
    utility::filesystem::DeleteDirectory(data_root + "/extract/" + prefix);

    data::DemoPoseGraphOptimization demo_pose_optimization(data_root);
    // Check if downloaded.
    EXPECT_TRUE(utility::filesystem::DirectoryExists(download_dir));

    // Methods to get path.
    EXPECT_EQ(demo_pose_optimization.GetPoseGraphFragmentPath(),
              extract_dir + "/pose_graph_example_fragment.json");
    EXPECT_EQ(demo_pose_optimization.GetPoseGraphGlobalPath(),
              extract_dir + "/pose_graph_example_global.json");

    // Basic methods.
    EXPECT_EQ(demo_pose_optimization.GetPrefix(), prefix);
    EXPECT_EQ(demo_pose_optimization.GetDataRoot(), data_root);
    EXPECT_EQ(demo_pose_optimization.GetDownloadDir(), download_dir);
    EXPECT_EQ(demo_pose_optimization.GetExtractDir(), extract_dir);

    // Delete dataset.
    utility::filesystem::DeleteDirectory(download_dir);
    utility::filesystem::DeleteDirectory(extract_dir);
}

TEST(Dataset, PCDPointCloud) {
    const std::string prefix = "PCDPointCloud";
    const std::string data_root = utility::filesystem::GetHomeDirectory() +
                                  "/open3d_data/open3d_test";
    const std::string download_dir = data_root + "/download/" + prefix;
    const std::string extract_dir = data_root + "/extract/" + prefix;

    // Delete if files already exists.
    utility::filesystem::DeleteDirectory(data_root + "/download/" + prefix);
    utility::filesystem::DeleteDirectory(data_root + "/extract/" + prefix);

    data::PCDPointCloud pointcloud_pcd(data_root);
    // Check if downloaded.
    EXPECT_TRUE(utility::filesystem::DirectoryExists(download_dir));

    // Method to get path.
    EXPECT_EQ(pointcloud_pcd.GetPath(), extract_dir + "/fragment.pcd");
    // Check if the file actually exists.
    EXPECT_TRUE(utility::filesystem::FileExists(pointcloud_pcd.GetPath()));

    // Basic method.
    EXPECT_EQ(pointcloud_pcd.GetPrefix(), prefix);
    EXPECT_EQ(pointcloud_pcd.GetDataRoot(), data_root);
    EXPECT_EQ(pointcloud_pcd.GetDownloadDir(), download_dir);
    EXPECT_EQ(pointcloud_pcd.GetExtractDir(), extract_dir);

    // Delete dataset.
    utility::filesystem::DeleteDirectory(download_dir);
    utility::filesystem::DeleteDirectory(extract_dir);
}

TEST(Dataset, PLYPointCloud) {
    const std::string prefix = "PLYPointCloud";
    const std::string data_root = utility::filesystem::GetHomeDirectory() +
                                  "/open3d_data/open3d_test";
    const std::string download_dir = data_root + "/download/" + prefix;
    const std::string extract_dir = data_root + "/extract/" + prefix;

    // Delete if files already exists.
    utility::filesystem::DeleteDirectory(data_root + "/download/" + prefix);
    utility::filesystem::DeleteDirectory(data_root + "/extract/" + prefix);

    data::PLYPointCloud pointcloud_ply(data_root);
    // Check if downloaded.
    EXPECT_TRUE(utility::filesystem::DirectoryExists(download_dir));

    // Method to get path.
    EXPECT_EQ(pointcloud_ply.GetPath(), extract_dir + "/fragment.ply");
    // Check if the file actually exists.
    EXPECT_TRUE(utility::filesystem::FileExists(pointcloud_ply.GetPath()));

    // Basic method.
    EXPECT_EQ(pointcloud_ply.GetPrefix(), prefix);
    EXPECT_EQ(pointcloud_ply.GetDataRoot(), data_root);
    EXPECT_EQ(pointcloud_ply.GetDownloadDir(), download_dir);
    EXPECT_EQ(pointcloud_ply.GetExtractDir(), extract_dir);

    // Delete dataset.
    utility::filesystem::DeleteDirectory(download_dir);
    utility::filesystem::DeleteDirectory(extract_dir);
}

TEST(Dataset, PTSPointCloud) {
    const std::string prefix = "PTSPointCloud";
    const std::string data_root = utility::filesystem::GetHomeDirectory() +
                                  "/open3d_data/open3d_test";
    const std::string download_dir = data_root + "/download/" + prefix;
    const std::string extract_dir = data_root + "/extract/" + prefix;

    // Delete if files already exists.
    utility::filesystem::DeleteDirectory(data_root + "/download/" + prefix);
    utility::filesystem::DeleteDirectory(data_root + "/extract/" + prefix);

    data::PTSPointCloud pointcloud_pts(data_root);
    // Check if downloaded.
    EXPECT_TRUE(utility::filesystem::DirectoryExists(download_dir));

    // Method to get path.
    EXPECT_EQ(pointcloud_pts.GetPath(),
              extract_dir + "/point_cloud_sample1.pts");
    // Check if the file actually exists.
    EXPECT_TRUE(utility::filesystem::FileExists(pointcloud_pts.GetPath()));

    // Basic method.
    EXPECT_EQ(pointcloud_pts.GetPrefix(), prefix);
    EXPECT_EQ(pointcloud_pts.GetDataRoot(), data_root);
    EXPECT_EQ(pointcloud_pts.GetDownloadDir(), download_dir);
    EXPECT_EQ(pointcloud_pts.GetExtractDir(), extract_dir);

    // Delete dataset.
    utility::filesystem::DeleteDirectory(download_dir);
    utility::filesystem::DeleteDirectory(extract_dir);
}

TEST(Dataset, SampleNYURGBDImage) {
    const std::string prefix = "SampleNYURGBDImage";
    const std::string data_root = utility::filesystem::GetHomeDirectory() +
                                  "/open3d_data/open3d_test";
    const std::string download_dir = data_root + "/download/" + prefix;
    const std::string extract_dir = data_root + "/extract/" + prefix;

    // Delete if files already exists.
    utility::filesystem::DeleteDirectory(data_root + "/download/" + prefix);
    utility::filesystem::DeleteDirectory(data_root + "/extract/" + prefix);

    data::SampleNYURGBDImage rgbd_nyu(data_root);
    // Check if downloaded.
    EXPECT_TRUE(utility::filesystem::DirectoryExists(download_dir));

    // Method to get path.
    EXPECT_EQ(rgbd_nyu.GetColorPath(), extract_dir + "/NYU_color.ppm");
    EXPECT_TRUE(utility::filesystem::FileExists(rgbd_nyu.GetColorPath()));
    EXPECT_EQ(rgbd_nyu.GetDepthPath(), extract_dir + "/NYU_depth.pgm");
    EXPECT_TRUE(utility::filesystem::FileExists(rgbd_nyu.GetDepthPath()));

    // Basic method.
    EXPECT_EQ(rgbd_nyu.GetPrefix(), prefix);
    EXPECT_EQ(rgbd_nyu.GetDataRoot(), data_root);
    EXPECT_EQ(rgbd_nyu.GetDownloadDir(), download_dir);
    EXPECT_EQ(rgbd_nyu.GetExtractDir(), extract_dir);

    // Delete dataset.
    utility::filesystem::DeleteDirectory(download_dir);
    utility::filesystem::DeleteDirectory(extract_dir);
}

TEST(Dataset, SampleSUNRGBDImage) {
    const std::string prefix = "SampleSUNRGBDImage";
    const std::string data_root = utility::filesystem::GetHomeDirectory() +
                                  "/open3d_data/open3d_test";
    const std::string download_dir = data_root + "/download/" + prefix;
    const std::string extract_dir = data_root + "/extract/" + prefix;

    // Delete if files already exists.
    utility::filesystem::DeleteDirectory(data_root + "/download/" + prefix);
    utility::filesystem::DeleteDirectory(data_root + "/extract/" + prefix);

    data::SampleSUNRGBDImage rgbd_sun(data_root);
    // Check if downloaded.
    EXPECT_TRUE(utility::filesystem::DirectoryExists(download_dir));

    // Method to get path.
    EXPECT_EQ(rgbd_sun.GetColorPath(), extract_dir + "/SUN_color.jpg");
    EXPECT_TRUE(utility::filesystem::FileExists(rgbd_sun.GetColorPath()));
    EXPECT_EQ(rgbd_sun.GetDepthPath(), extract_dir + "/SUN_depth.png");
    EXPECT_TRUE(utility::filesystem::FileExists(rgbd_sun.GetDepthPath()));

    // Basic method.
    EXPECT_EQ(rgbd_sun.GetPrefix(), prefix);
    EXPECT_EQ(rgbd_sun.GetDataRoot(), data_root);
    EXPECT_EQ(rgbd_sun.GetDownloadDir(), download_dir);
    EXPECT_EQ(rgbd_sun.GetExtractDir(), extract_dir);

    // Delete dataset.
    utility::filesystem::DeleteDirectory(download_dir);
    utility::filesystem::DeleteDirectory(extract_dir);
}

TEST(Dataset, SampleTUMRGBDImage) {
    const std::string prefix = "SampleTUMRGBDImage";
    const std::string data_root = utility::filesystem::GetHomeDirectory() +
                                  "/open3d_data/open3d_test";
    const std::string download_dir = data_root + "/download/" + prefix;
    const std::string extract_dir = data_root + "/extract/" + prefix;

    // Delete if files already exists.
    utility::filesystem::DeleteDirectory(data_root + "/download/" + prefix);
    utility::filesystem::DeleteDirectory(data_root + "/extract/" + prefix);

    data::SampleTUMRGBDImage rgbd_tum(data_root);
    // Check if downloaded.
    EXPECT_TRUE(utility::filesystem::DirectoryExists(download_dir));

    // Method to get path.
    EXPECT_EQ(rgbd_tum.GetColorPath(), extract_dir + "/TUM_color.png");
    EXPECT_TRUE(utility::filesystem::FileExists(rgbd_tum.GetColorPath()));
    EXPECT_EQ(rgbd_tum.GetDepthPath(), extract_dir + "/TUM_depth.png");
    EXPECT_TRUE(utility::filesystem::FileExists(rgbd_tum.GetDepthPath()));

    // Basic method.
    EXPECT_EQ(rgbd_tum.GetPrefix(), prefix);
    EXPECT_EQ(rgbd_tum.GetDataRoot(), data_root);
    EXPECT_EQ(rgbd_tum.GetDownloadDir(), download_dir);
    EXPECT_EQ(rgbd_tum.GetExtractDir(), extract_dir);

    // Delete dataset.
    utility::filesystem::DeleteDirectory(download_dir);
    utility::filesystem::DeleteDirectory(extract_dir);
}

TEST(Dataset, SampleRedwoodRGBDImages) {
    const std::string prefix = "SampleRedwoodRGBDImages";
    const std::string data_root = utility::filesystem::GetHomeDirectory() +
                                  "/open3d_data/open3d_test";
    const std::string download_dir = data_root + "/download/" + prefix;
    const std::string extract_dir = data_root + "/extract/" + prefix;

    // Delete if files already exists.
    utility::filesystem::DeleteDirectory(data_root + "/download/" + prefix);
    utility::filesystem::DeleteDirectory(data_root + "/extract/" + prefix);

    data::SampleRedwoodRGBDImages rgbd_redwood(data_root);
    // Check if downloaded.
    EXPECT_TRUE(utility::filesystem::DirectoryExists(download_dir));

    // Method to get path.
    const std::vector<std::string> color_paths = {
            extract_dir + "/color/00000.jpg", extract_dir + "/color/00001.jpg",
            extract_dir + "/color/00002.jpg", extract_dir + "/color/00003.jpg",
            extract_dir + "/color/00004.jpg"};
    EXPECT_EQ(rgbd_redwood.GetColorPaths(), color_paths);

    const std::vector<std::string> depth_paths = {
            extract_dir + "/depth/00000.png", extract_dir + "/depth/00001.png",
            extract_dir + "/depth/00002.png", extract_dir + "/depth/00003.png",
            extract_dir + "/depth/00004.png"};
    EXPECT_EQ(rgbd_redwood.GetDepthPaths(), depth_paths);
    for (size_t i = 0; i < color_paths.size(); ++i) {
        EXPECT_TRUE(utility::filesystem::FileExists(
                rgbd_redwood.GetColorPaths()[i]));
        EXPECT_TRUE(utility::filesystem::FileExists(
                rgbd_redwood.GetDepthPaths()[i]));
    }

    EXPECT_EQ(rgbd_redwood.GetTrajectoryLogPath(),
              extract_dir + "/trajectory.log");
    EXPECT_TRUE(utility::filesystem::FileExists(
            rgbd_redwood.GetTrajectoryLogPath()));

    EXPECT_EQ(rgbd_redwood.GetOdometryLogPath(), extract_dir + "/odometry.log");
    EXPECT_TRUE(
            utility::filesystem::FileExists(rgbd_redwood.GetOdometryLogPath()));

    EXPECT_EQ(rgbd_redwood.GetRGBDMatchPath(), extract_dir + "/rgbd.match");
    EXPECT_TRUE(
            utility::filesystem::FileExists(rgbd_redwood.GetRGBDMatchPath()));

    EXPECT_EQ(rgbd_redwood.GetReconstructionPath(),
              extract_dir + "/example_tsdf_pcd.ply");
    EXPECT_TRUE(utility::filesystem::FileExists(
            rgbd_redwood.GetReconstructionPath()));

    // Basic method.
    EXPECT_EQ(rgbd_redwood.GetPrefix(), prefix);
    EXPECT_EQ(rgbd_redwood.GetDataRoot(), data_root);
    EXPECT_EQ(rgbd_redwood.GetDownloadDir(), download_dir);
    EXPECT_EQ(rgbd_redwood.GetExtractDir(), extract_dir);

    // Delete dataset.
    utility::filesystem::DeleteDirectory(download_dir);
    utility::filesystem::DeleteDirectory(extract_dir);
}

TEST(Dataset, SampleFountainRGBDImages) {
    const std::string prefix = "SampleFountainRGBDImages";
    const std::string data_root = utility::filesystem::GetHomeDirectory() +
                                  "/open3d_data/open3d_test";
    const std::string download_dir = data_root + "/download/" + prefix;
    const std::string extract_dir = data_root + "/extract/" + prefix;

    // Delete if files already exists.
    utility::filesystem::DeleteDirectory(data_root + "/download/" + prefix);
    utility::filesystem::DeleteDirectory(data_root + "/extract/" + prefix);

    data::SampleFountainRGBDImages rgbd_fountain(data_root);
    // Check if downloaded.
    EXPECT_TRUE(utility::filesystem::DirectoryExists(download_dir));

    // Method to get path.
    const std::vector<std::string> color_paths = {
            extract_dir + "/image/0000010-000001228920.jpg",
            extract_dir + "/image/0000031-000004096400.jpg",
            extract_dir + "/image/0000044-000005871507.jpg",
            extract_dir + "/image/0000064-000008602440.jpg",
            extract_dir + "/image/0000110-000014883587.jpg",
            extract_dir + "/image/0000156-000021164733.jpg",
            extract_dir + "/image/0000200-000027172787.jpg",
            extract_dir + "/image/0000215-000029220987.jpg",
            extract_dir + "/image/0000255-000034682853.jpg",
            extract_dir + "/image/0000299-000040690907.jpg",
            extract_dir + "/image/0000331-000045060400.jpg",
            extract_dir + "/image/0000368-000050112627.jpg",
            extract_dir + "/image/0000412-000056120680.jpg",
            extract_dir + "/image/0000429-000058441973.jpg",
            extract_dir + "/image/0000474-000064586573.jpg",
            extract_dir + "/image/0000487-000066361680.jpg",
            extract_dir + "/image/0000526-000071687000.jpg",
            extract_dir + "/image/0000549-000074827573.jpg",
            extract_dir + "/image/0000582-000079333613.jpg",
            extract_dir + "/image/0000630-000085887853.jpg",
            extract_dir + "/image/0000655-000089301520.jpg",
            extract_dir + "/image/0000703-000095855760.jpg",
            extract_dir + "/image/0000722-000098450147.jpg",
            extract_dir + "/image/0000771-000105140933.jpg",
            extract_dir + "/image/0000792-000108008413.jpg",
            extract_dir + "/image/0000818-000111558627.jpg",
            extract_dir + "/image/0000849-000115791573.jpg",
            extract_dir + "/image/0000883-000120434160.jpg",
            extract_dir + "/image/0000896-000122209267.jpg",
            extract_dir + "/image/0000935-000127534587.jpg",
            extract_dir + "/image/0000985-000134361920.jpg",
            extract_dir + "/image/0001028-000140233427.jpg",
            extract_dir + "/image/0001061-000144739467.jpg"};
    EXPECT_EQ(rgbd_fountain.GetColorPaths(), color_paths);

    const std::vector<std::string> depth_paths = {
            extract_dir + "/depth/0000038-000001234662.png",
            extract_dir + "/depth/0000124-000004104418.png",
            extract_dir + "/depth/0000177-000005872988.png",
            extract_dir + "/depth/0000259-000008609267.png",
            extract_dir + "/depth/0000447-000014882686.png",
            extract_dir + "/depth/0000635-000021156105.png",
            extract_dir + "/depth/0000815-000027162570.png",
            extract_dir + "/depth/0000877-000029231463.png",
            extract_dir + "/depth/0001040-000034670651.png",
            extract_dir + "/depth/0001220-000040677116.png",
            extract_dir + "/depth/0001351-000045048488.png",
            extract_dir + "/depth/0001503-000050120614.png",
            extract_dir + "/depth/0001683-000056127079.png",
            extract_dir + "/depth/0001752-000058429557.png",
            extract_dir + "/depth/0001937-000064602868.png",
            extract_dir + "/depth/0001990-000066371438.png",
            extract_dir + "/depth/0002149-000071677149.png",
            extract_dir + "/depth/0002243-000074813859.png",
            extract_dir + "/depth/0002378-000079318707.png",
            extract_dir + "/depth/0002575-000085892450.png",
            extract_dir + "/depth/0002677-000089296113.png",
            extract_dir + "/depth/0002874-000095869855.png",
            extract_dir + "/depth/0002951-000098439288.png",
            extract_dir + "/depth/0003152-000105146507.png",
            extract_dir + "/depth/0003238-000108016262.png",
            extract_dir + "/depth/0003344-000111553403.png",
            extract_dir + "/depth/0003471-000115791298.png",
            extract_dir + "/depth/0003610-000120429623.png",
            extract_dir + "/depth/0003663-000122198194.png",
            extract_dir + "/depth/0003823-000127537274.png",
            extract_dir + "/depth/0004028-000134377970.png",
            extract_dir + "/depth/0004203-000140217589.png",
            extract_dir + "/depth/0004339-000144755807.png"};
    EXPECT_EQ(rgbd_fountain.GetDepthPaths(), depth_paths);

    for (auto& color_path : rgbd_fountain.GetColorPaths()) {
        EXPECT_TRUE(utility::filesystem::FileExists(color_path));
    }
    for (auto& depth_path : rgbd_fountain.GetDepthPaths()) {
        EXPECT_TRUE(utility::filesystem::FileExists(depth_path));
    }

    EXPECT_EQ(rgbd_fountain.GetKeyframePosesLogPath(),
              extract_dir + "/scene/key.log");
    EXPECT_TRUE(utility::filesystem::FileExists(
            rgbd_fountain.GetKeyframePosesLogPath()));

    EXPECT_EQ(rgbd_fountain.GetReconstructionPath(),
              extract_dir + "/scene/integrated.ply");
    EXPECT_TRUE(utility::filesystem::FileExists(
            rgbd_fountain.GetReconstructionPath()));

    // Basic method.
    EXPECT_EQ(rgbd_fountain.GetPrefix(), prefix);
    EXPECT_EQ(rgbd_fountain.GetDataRoot(), data_root);
    EXPECT_EQ(rgbd_fountain.GetDownloadDir(), download_dir);
    EXPECT_EQ(rgbd_fountain.GetExtractDir(), extract_dir);

    // Delete dataset.
    utility::filesystem::DeleteDirectory(download_dir);
    utility::filesystem::DeleteDirectory(extract_dir);
}

TEST(Dataset, SampleL515Bag) {
    const std::string prefix = "SampleL515Bag";
    const std::string data_root = utility::filesystem::GetHomeDirectory() +
                                  "/open3d_data/open3d_test";
    const std::string download_dir = data_root + "/download/" + prefix;
    const std::string extract_dir = data_root + "/extract/" + prefix;

    // Delete if files already exists.
    utility::filesystem::DeleteDirectory(data_root + "/download/" + prefix);
    utility::filesystem::DeleteDirectory(data_root + "/extract/" + prefix);

    data::SampleL515Bag sample_bag(data_root);
    // Check if downloaded.
    EXPECT_TRUE(utility::filesystem::DirectoryExists(download_dir));

    // Method to get path.
    EXPECT_EQ(sample_bag.GetPath(), extract_dir + "/L515_test_s.bag");
    // Check if the file actually exists.
    EXPECT_TRUE(utility::filesystem::FileExists(sample_bag.GetPath()));

    // Basic method.
    EXPECT_EQ(sample_bag.GetPrefix(), prefix);
    EXPECT_EQ(sample_bag.GetDataRoot(), data_root);
    EXPECT_EQ(sample_bag.GetDownloadDir(), download_dir);
    EXPECT_EQ(sample_bag.GetExtractDir(), extract_dir);

    // Delete dataset.
    utility::filesystem::DeleteDirectory(download_dir);
    utility::filesystem::DeleteDirectory(extract_dir);
}

TEST(Dataset, EaglePointCloud) {
    const std::string prefix = "EaglePointCloud";
    const std::string data_root = utility::filesystem::GetHomeDirectory() +
                                  "/open3d_data/open3d_test";
    const std::string download_dir = data_root + "/download/" + prefix;
    const std::string extract_dir = data_root + "/extract/" + prefix;

    // Delete if files already exists.
    utility::filesystem::DeleteDirectory(data_root + "/download/" + prefix);
    utility::filesystem::DeleteDirectory(data_root + "/extract/" + prefix);

    data::EaglePointCloud eagle(data_root);
    // Check if downloaded.
    EXPECT_TRUE(utility::filesystem::DirectoryExists(download_dir));

    // Method to get path.
    EXPECT_EQ(eagle.GetPath(), extract_dir + "/EaglePointCloud.ply");
    // Check if the file actually exists.
    EXPECT_TRUE(utility::filesystem::FileExists(eagle.GetPath()));

    // Basic method.
    EXPECT_EQ(eagle.GetPrefix(), prefix);
    EXPECT_EQ(eagle.GetDataRoot(), data_root);
    EXPECT_EQ(eagle.GetDownloadDir(), download_dir);
    EXPECT_EQ(eagle.GetExtractDir(), extract_dir);

    // Delete dataset.
    utility::filesystem::DeleteDirectory(download_dir);
    utility::filesystem::DeleteDirectory(extract_dir);
}

TEST(Dataset, ArmadilloMesh) {
    const std::string prefix = "ArmadilloMesh";
    const std::string data_root = utility::filesystem::GetHomeDirectory() +
                                  "/open3d_data/open3d_test";
    const std::string download_dir = data_root + "/download/" + prefix;
    const std::string extract_dir = data_root + "/extract/" + prefix;

    // Delete if files already exists.
    utility::filesystem::DeleteDirectory(data_root + "/download/" + prefix);
    utility::filesystem::DeleteDirectory(data_root + "/extract/" + prefix);

    data::ArmadilloMesh armadillo(data_root);
    // Check if downloaded.
    EXPECT_TRUE(utility::filesystem::DirectoryExists(download_dir));

    // Method to get path.
    EXPECT_EQ(armadillo.GetPath(), extract_dir + "/ArmadilloMesh.ply");
    // Check if the file actually exists.
    EXPECT_TRUE(utility::filesystem::FileExists(armadillo.GetPath()));

    // Basic method.
    EXPECT_EQ(armadillo.GetPrefix(), prefix);
    EXPECT_EQ(armadillo.GetDataRoot(), data_root);
    EXPECT_EQ(armadillo.GetDownloadDir(), download_dir);
    EXPECT_EQ(armadillo.GetExtractDir(), extract_dir);

    // Delete dataset.
    utility::filesystem::DeleteDirectory(download_dir);
    utility::filesystem::DeleteDirectory(extract_dir);
}

TEST(Dataset, BunnyMesh) {
    const std::string prefix = "BunnyMesh";
    const std::string data_root = utility::filesystem::GetHomeDirectory() +
                                  "/open3d_data/open3d_test";
    const std::string download_dir = data_root + "/download/" + prefix;
    const std::string extract_dir = data_root + "/extract/" + prefix;

    // Delete if files already exists.
    utility::filesystem::DeleteDirectory(data_root + "/download/" + prefix);
    utility::filesystem::DeleteDirectory(data_root + "/extract/" + prefix);

    data::BunnyMesh bunny(data_root);
    // Check if downloaded.
    EXPECT_TRUE(utility::filesystem::DirectoryExists(download_dir));

    // Method to get path.
    EXPECT_EQ(bunny.GetPath(), extract_dir + "/BunnyMesh.ply");
    // Check if the file actually exists.
    EXPECT_TRUE(utility::filesystem::FileExists(bunny.GetPath()));

    // Basic method.
    EXPECT_EQ(bunny.GetPrefix(), prefix);
    EXPECT_EQ(bunny.GetDataRoot(), data_root);
    EXPECT_EQ(bunny.GetDownloadDir(), download_dir);
    EXPECT_EQ(bunny.GetExtractDir(), extract_dir);

    // Delete dataset.
    utility::filesystem::DeleteDirectory(download_dir);
    utility::filesystem::DeleteDirectory(extract_dir);
}

TEST(Dataset, KnotMesh) {
    const std::string prefix = "KnotMesh";
    const std::string data_root = utility::filesystem::GetHomeDirectory() +
                                  "/open3d_data/open3d_test";
    const std::string download_dir = data_root + "/download/" + prefix;
    const std::string extract_dir = data_root + "/extract/" + prefix;

    // Delete if files already exists.
    utility::filesystem::DeleteDirectory(data_root + "/download/" + prefix);
    utility::filesystem::DeleteDirectory(data_root + "/extract/" + prefix);

    data::KnotMesh knot(data_root);
    // Check if downloaded.
    EXPECT_TRUE(utility::filesystem::DirectoryExists(download_dir));

    // Method to get path.
    EXPECT_EQ(knot.GetPath(), extract_dir + "/KnotMesh.ply");
    // Check if the file actually exists.
    EXPECT_TRUE(utility::filesystem::FileExists(knot.GetPath()));

    // Basic method.
    EXPECT_EQ(knot.GetPrefix(), prefix);
    EXPECT_EQ(knot.GetDataRoot(), data_root);
    EXPECT_EQ(knot.GetDownloadDir(), download_dir);
    EXPECT_EQ(knot.GetExtractDir(), extract_dir);

    // Delete dataset.
    utility::filesystem::DeleteDirectory(download_dir);
    utility::filesystem::DeleteDirectory(extract_dir);
}

TEST(Dataset, MonkeyModel) {
    const std::string prefix = "MonkeyModel";
    const std::string data_root = utility::filesystem::GetHomeDirectory() +
                                  "/open3d_data/open3d_test";
    const std::string download_dir = data_root + "/download/" + prefix;
    const std::string extract_dir = data_root + "/extract/" + prefix;

    // Delete if files already exists.
    utility::filesystem::DeleteDirectory(data_root + "/download/" + prefix);
    utility::filesystem::DeleteDirectory(data_root + "/extract/" + prefix);

    data::MonkeyModel monkey_model(data_root);
    // Check if downloaded.
    EXPECT_TRUE(utility::filesystem::DirectoryExists(download_dir));

    // Method to get path.
    std::unordered_map<std::string, std::string> map_filename_to_path = {
            {"albedo", extract_dir + "/albedo.png"},
            {"ao", extract_dir + "/ao.png"},
            {"metallic", extract_dir + "/metallic.png"},
            {"monkey_material", extract_dir + "/monkey.mtl"},
            {"monkey_model", extract_dir + "/monkey.obj"},
            {"monkey_solid_material", extract_dir + "/monkey_solid.mtl"},
            {"monkey_solid_model", extract_dir + "/monkey_solid.obj"},
            {"normal", extract_dir + "/normal.png"},
            {"roughness", extract_dir + "/roughness.png"}};

    for (auto file_name : monkey_model.GetPathMap()) {
        // Check the path map.
        EXPECT_EQ(map_filename_to_path.at(file_name.first), file_name.second);
        // Check the `GetPath` method.
        EXPECT_EQ(monkey_model.GetPath(file_name.first), file_name.second);
        // Check if the file path exists.
        EXPECT_TRUE(utility::filesystem::FileExists(file_name.second));
    }

    // Basic method.
    EXPECT_EQ(monkey_model.GetPrefix(), prefix);
    EXPECT_EQ(monkey_model.GetDataRoot(), data_root);
    EXPECT_EQ(monkey_model.GetDownloadDir(), download_dir);
    EXPECT_EQ(monkey_model.GetExtractDir(), extract_dir);

    // Delete dataset.
    utility::filesystem::DeleteDirectory(download_dir);
    utility::filesystem::DeleteDirectory(extract_dir);
}

TEST(Dataset, SwordModel) {
    const std::string prefix = "SwordModel";
    const std::string data_root = utility::filesystem::GetHomeDirectory() +
                                  "/open3d_data/open3d_test";
    const std::string download_dir = data_root + "/download/" + prefix;
    const std::string extract_dir = data_root + "/extract/" + prefix;

    // Delete if files already exists.
    utility::filesystem::DeleteDirectory(data_root + "/download/" + prefix);
    utility::filesystem::DeleteDirectory(data_root + "/extract/" + prefix);

    data::SwordModel sword_model(data_root);
    // Check if downloaded.
    EXPECT_TRUE(utility::filesystem::DirectoryExists(download_dir));

    // Method to get path.
    std::unordered_map<std::string, std::string> map_filename_to_path = {
            {"sword_material", extract_dir + "/UV.mtl"},
            {"sword_model", extract_dir + "/UV.obj"},
            {"base_color", extract_dir + "/UV_blinn1SG_BaseColor.png"},
            {"metallic", extract_dir + "/UV_blinn1SG_Metallic.png"},
            {"normal", extract_dir + "/UV_blinn1SG_Normal.png"},
            {"roughness", extract_dir + "/UV_blinn1SG_Roughness.png"}};

    for (auto file_name : sword_model.GetPathMap()) {
        // Check the path map.
        EXPECT_EQ(map_filename_to_path.at(file_name.first), file_name.second);
        // Check the `GetPath` method.
        EXPECT_EQ(sword_model.GetPath(file_name.first), file_name.second);
        // Check if the file path exists.
        EXPECT_TRUE(utility::filesystem::FileExists(file_name.second));
    }

    // Basic method.
    EXPECT_EQ(sword_model.GetPrefix(), prefix);
    EXPECT_EQ(sword_model.GetDataRoot(), data_root);
    EXPECT_EQ(sword_model.GetDownloadDir(), download_dir);
    EXPECT_EQ(sword_model.GetExtractDir(), extract_dir);

    // Delete dataset.
    utility::filesystem::DeleteDirectory(download_dir);
    utility::filesystem::DeleteDirectory(extract_dir);
}

TEST(Dataset, CrateModel) {
    const std::string prefix = "CrateModel";
    const std::string data_root = utility::filesystem::GetHomeDirectory() +
                                  "/open3d_data/open3d_test";
    const std::string download_dir = data_root + "/download/" + prefix;
    const std::string extract_dir = data_root + "/extract/" + prefix;

    // Delete if files already exists.
    utility::filesystem::DeleteDirectory(data_root + "/download/" + prefix);
    utility::filesystem::DeleteDirectory(data_root + "/extract/" + prefix);

    data::CrateModel crate_model(data_root);
    // Check if downloaded.
    EXPECT_TRUE(utility::filesystem::DirectoryExists(download_dir));

    // Method to get path.
    std::unordered_map<std::string, std::string> map_filename_to_path = {
            {"create_material", extract_dir + "/crate.mtl"},
            {"create_model", extract_dir + "/crate.obj"},
            {"texture_image", extract_dir + "/crate.jpg"}};

    for (auto file_name : crate_model.GetPathMap()) {
        // Check the path map.
        EXPECT_EQ(map_filename_to_path.at(file_name.first), file_name.second);
        // Check the `GetPath` method.
        EXPECT_EQ(crate_model.GetPath(file_name.first), file_name.second);
        // Check if the file path exists.
        EXPECT_TRUE(utility::filesystem::FileExists(file_name.second));
    }

    // Basic method.
    EXPECT_EQ(crate_model.GetPrefix(), prefix);
    EXPECT_EQ(crate_model.GetDataRoot(), data_root);
    EXPECT_EQ(crate_model.GetDownloadDir(), download_dir);
    EXPECT_EQ(crate_model.GetExtractDir(), extract_dir);

    // Delete dataset.
    utility::filesystem::DeleteDirectory(download_dir);
    utility::filesystem::DeleteDirectory(extract_dir);
}

TEST(Dataset, JuneauImage) {
    const std::string prefix = "JuneauImage";
    const std::string data_root = utility::filesystem::GetHomeDirectory() +
                                  "/open3d_data/open3d_test";
    const std::string download_dir = data_root + "/download/" + prefix;
    const std::string extract_dir = data_root + "/extract/" + prefix;

    // Delete if files already exists.
    utility::filesystem::DeleteDirectory(data_root + "/download/" + prefix);
    utility::filesystem::DeleteDirectory(data_root + "/extract/" + prefix);

    data::JuneauImage juneau(data_root);
    // Check if downloaded.
    EXPECT_TRUE(utility::filesystem::DirectoryExists(download_dir));

    // Method to get path.
    EXPECT_EQ(juneau.GetPath(), extract_dir + "/JuneauImage.jpg");
    // Check if the file actually exists.
    EXPECT_TRUE(utility::filesystem::FileExists(juneau.GetPath()));

    // Basic method.
    EXPECT_EQ(juneau.GetPrefix(), prefix);
    EXPECT_EQ(juneau.GetDataRoot(), data_root);
    EXPECT_EQ(juneau.GetDownloadDir(), download_dir);
    EXPECT_EQ(juneau.GetExtractDir(), extract_dir);

    // Delete dataset.
    utility::filesystem::DeleteDirectory(download_dir);
    utility::filesystem::DeleteDirectory(extract_dir);
}

TEST(Dataset, DISABLED_RedwoodLivingRoomPointClouds) {
    const std::string prefix = "LivingRoomPointClouds";
    const std::string data_root = utility::filesystem::GetHomeDirectory() +
                                  "/open3d_data/open3d_test";
    const std::string download_dir = data_root + "/download/" + prefix;
    const std::string extract_dir = data_root + "/extract/" + prefix;

    // Delete if files already exists.
    utility::filesystem::DeleteDirectory(data_root + "/download/" + prefix);
    utility::filesystem::DeleteDirectory(data_root + "/extract/" + prefix);

    data::LivingRoomPointClouds living_room(data_root);
    // Check if downloaded.
    EXPECT_TRUE(utility::filesystem::DirectoryExists(download_dir));

    // Methods to get path.
    std::vector<std::string> paths;
    paths.reserve(57);
    for (int i = 0; i < 57; ++i) {
        paths.push_back(extract_dir + "/cloud_bin_" + std::to_string(i) +
                        ".ply");
    }
    EXPECT_EQ(living_room.GetPaths(), paths);
    for (size_t i = 0; i < paths.size(); ++i) {
        EXPECT_EQ(living_room.GetPaths(i), paths[i]);
        // Check if the file actually exists.
        EXPECT_TRUE(utility::filesystem::FileExists(living_room.GetPaths(i)));
    }

    // Basic methods.
    EXPECT_EQ(living_room.GetPrefix(), prefix);
    EXPECT_EQ(living_room.GetDataRoot(), data_root);
    EXPECT_EQ(living_room.GetDownloadDir(), download_dir);
    EXPECT_EQ(living_room.GetExtractDir(), extract_dir);

    // Delete dataset.
    utility::filesystem::DeleteDirectory(download_dir);
    utility::filesystem::DeleteDirectory(extract_dir);
}

TEST(Dataset, DISABLED_RedwoodOfficePointClouds) {
    const std::string prefix = "OfficePointClouds";
    const std::string data_root = utility::filesystem::GetHomeDirectory() +
                                  "/open3d_data/open3d_test";
    const std::string download_dir = data_root + "/download/" + prefix;
    const std::string extract_dir = data_root + "/extract/" + prefix;

    // Delete if files already exists.
    utility::filesystem::DeleteDirectory(data_root + "/download/" + prefix);
    utility::filesystem::DeleteDirectory(data_root + "/extract/" + prefix);

    data::OfficePointClouds office(data_root);
    // Check if downloaded.
    EXPECT_TRUE(utility::filesystem::DirectoryExists(download_dir));

    // Methods to get path.
    std::vector<std::string> paths;
    paths.reserve(53);
    for (int i = 0; i < 53; ++i) {
        paths.push_back(extract_dir + "/cloud_bin_" + std::to_string(i) +
                        ".ply");
    }
    EXPECT_EQ(office.GetPaths(), paths);
    for (size_t i = 0; i < paths.size(); ++i) {
        EXPECT_EQ(office.GetPaths(i), paths[i]);
        // Check if the file actually exists.
        EXPECT_TRUE(utility::filesystem::FileExists(office.GetPaths(i)));
    }

    EXPECT_EQ(office.GetPaths(), paths);
    for (size_t i = 0; i < paths.size(); ++i) {
        EXPECT_EQ(office.GetPaths(i), paths[i]);
        // Check if the file actually exists.
        EXPECT_TRUE(utility::filesystem::FileExists(office.GetPaths(i)));
    }

    // Basic methods.
    EXPECT_EQ(office.GetPrefix(), prefix);
    EXPECT_EQ(office.GetDataRoot(), data_root);
    EXPECT_EQ(office.GetDownloadDir(), download_dir);
    EXPECT_EQ(office.GetExtractDir(), extract_dir);

    // Delete dataset.
    utility::filesystem::DeleteDirectory(download_dir);
    utility::filesystem::DeleteDirectory(extract_dir);
}

}  // namespace tests
}  // namespace open3d
