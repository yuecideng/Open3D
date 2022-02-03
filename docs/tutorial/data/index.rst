.. _data:

Data Module
===========

TODO:

1. Fuse the description into the first code examples.
2. See if we can make Python/C++ code in tabs.

Open3D provides `open3d.data` module for convenient access to built-in
example and test data. You'll need internet access to use the data module.
The downloaded data will be stored in the Open3D's data root directory.

A dataset class locates the data root directory in the following order:

1. User-specified by ``data_root`` when instantiating a dataset object.
2. OPEN3D_DATA_ROOT environment variable.
3. $HOME/open3d_data.

By default, (3) will be used, and it is also the recommended way.

When a dataset object is instantiated, the corresponding data will be
downloaded in `${data_root}/download/prefix/` and extracted or copied to
`${data_root}/extract/prefix/`. If the extracted data directory exists,
the files will be used without validation. If it does not exist, and the
valid downloaded file exists, the data will be extracted from the
downloaded file. If the downloaded file does not exist or validates against
the provided MD5, it will be re-downloaded.

After the data is downloaded and extracted, the dataset object will NOT
load the data for you. Instead, you will get the paths to the data files
and use Open3D's I/O functions to load the data. This design exposes where
the data is stored and how the data is loaded, allowing users to modify
the code and load their own data in a similar way. Please check the
documentation of the specific dataset to know more about the specific
functionalities provided for it.

Example of loading a simple Bunny TriangleMesh using the data module:

.. code-block:: Python

    import open3d as o3d

    # Show how to specify a download prefix
    bunny_data = open3d.data.BunnyMesh()

    mesh = open3d.io.read_triangle_mesh(bunny_data.path)
    o3d.visualization.draw([pcd])

    # Todo add a more complex example, camera, rgbd, etc.


.. code-block:: C++

    #include "open3d/Open3D.h"
    using namespace open3d;

    // Show how to specify a download prefix
    data::BunnyMesh bunny_data;
    geometry::TriangleMesh mesh;
    io::ReadTriangleMesh(bunny_data.path, mesh);
    mesh.ComputeVertexNormals();
    visualization::Draw({mesh});

    // Todo add a more complex example, camera, rgbd, etc.


Point Cloud Data
~~~~~~~~~~~~~~~~

``SamplePointCloudPCD``
-----------------------

TODO: Very short description, e.g. what this is, what type of geometry, where
is comes from.

.. code-block:: Python

    pcd_data = o3d.data.SamplePointCloudPCD()
    pcd = o3d.io.read_point_cloud(pcd_data.path)

.. code-block:: C++

    data::SamplePointCloudPCD dataset;
    geometry::PointCloud pcd = io::ReadPointCloud(dataset.path);


Sample PointCloud PLY
----------------------------------------

Loading and visualizing example:

.. code-block:: Python

    pcd_data = open3d.data.SamplePointCloudPCD()
    pcd = open3d.io.read_point_cloud(pcd_data.path)
    open3d.visualization.draw([pcd])


.. code-block:: C++

    pcd_data = open3d::data::SamplePointCloudPCD();
    pcd = open3d::io::ReadPointCloud(pcd_data.path);
    open3d::visualization::Draw({pcd});

Mirror(s):
    - `Mirror 1 <https://github.com/isl-org/open3d_downloads/releases/download/20220201-data/fragment.ply>`_
Contents:
    fragment.ply
Source:
    Living Room point cloud fragment from Redwood RGB-D livingroom1 sequence.
Licence:
    Creative Commons 3.0 (CC BY 3.0).


Eagle
----------------------------------------

Loading and visualizing example:

.. code-block:: Python

        pcd_data = open3d.data.EaglePointCloud()
        pcd = open3d.io.read_point_cloud(pcd_data.path)
        open3d.visualization.draw([pcd])


.. code-block:: C++

        pcd_data = open3d::data::EaglePointCloud();
        pcd = open3d::io::ReadPointCloud(pcd_data.path);
        open3d::visualization::Draw({pcd});

Mirror(s):
    - `Mirror 1 <https://github.com/isl-org/open3d_downloads/releases/download/20220201-data/EaglePointCloud.ply>`_
Contents:
    EaglePointCloud.ply
Source:
    xxx
Licence:
    Creative Commons 3.0 (CC BY 3.0).


Redwood Living Room PointCloud Fragments
----------------------------------------

Loading and visualizing example:

.. code-block:: Python

        pcd_fragments_data = open3d.data.RedwoodLivingRoomPointCloud()
        for path in pcd_fragments_data.paths:
            pcd = open3d.io.read_point_cloud(pcd_fragments_data.path)
            o3d.visualization.draw([pcd])


.. code-block:: C++

        pcd_fragments_data = open3d::data::RedwoodLivingRoomPointCloud();
        for(const std::string& path : pcd_fragments_data.path) {
            pcd = open3d::io::ReadPointCloud(pcd_data.path);
            open3d::visualization::Draw({pcd});
        }

Mirror(s):
    - `Mirror 1 <http://redwood-data.org/indoor/data/livingroom1-fragments-ply.zip>`_
    - `Mirror 2 <https://github.com/isl-org/open3d_downloads/releases/download/redwood/livingroom1-fragments-ply.zip>`_
Contents:
    .. code-block::

            livingroom1-fragments-ply.zip
            ├── cloud_bin_0.ply
            ├── cloud_bin_1.ply
            ├── ...
            └── cloud_bin_56.ply

Source:
    Living Room point cloud fragments from Redwood RGB-D livingroom1 sequence.
Licence:
    Creative Commons 3.0 (CC BY 3.0).


Redwood Office PointCloud Fragments
----------------------------------------

Loading and visualizing example:

.. code-block:: Python

        pcd_fragments_data = open3d.data.RedwoodOfficePointCloud()
        for path in pcd_fragments_data.paths:
            pcd = open3d.io.read_point_cloud(pcd_fragments_data.path)
            o3d.visualization.draw([pcd])


.. code-block:: C++

        pcd_fragments_data = open3d::data::RedwoodOfficePointCloud();
        for(const std::string& path : pcd_fragments_data.path) {
            pcd = open3d::io::ReadPointCloud(pcd_data.path);
            open3d::visualization::Draw({pcd});
        }

Mirror(s):
    - `Mirror 1 <http://redwood-data.org/indoor/data/livingroom1-fragments-ply.zip>`_
    - `Mirror 2 <https://github.com/isl-org/open3d_downloads/releases/download/redwood/livingroom1-fragments-ply.zip>`_
Contents:
    .. code-block::

            office1-fragments-ply.zip
            ├── cloud_bin_0.ply
            ├── cloud_bin_1.ply
            ├── ...
            └── cloud_bin_52.ply

Source:
    Office point cloud fragments from Redwood RGB-D office1 sequence.
Licence:
    Creative Commons 3.0 (CC BY 3.0).


Triangle Mesh Data
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


Bunny
----------------------------------------

Loading and visualizing example:

.. code-block:: Python

        mesh_data = open3d.data.BunnyMesh()
        mesh = open3d.io.read_triangle_mesh(mesh_data.path)
        o3d.visualization.draw([mesh])


.. code-block:: C++

        mesh_data = open3d::data::BunnyMesh();
        mesh = open3d::io::ReadTriangleMesh(mesh_data.path);
        open3d::visualization::Draw({mesh});

Mirror(s):
    - `Mirror 1 <https://github.com/isl-org/open3d_downloads/releases/download/20220201-data/BunnyMesh.ply>`_
Contents:
    BunnyMesh.ply
Source:
    Stanford University Computer Graphics Laboratory.
Licence:
    Creative Commons 3.0 (CC BY 3.0).


Armadillo
----------------------------------------

Loading and visualizing example:

.. code-block:: Python

        mesh_data = open3d.data.ArmadilloMesh()
        mesh = open3d.io.read_triangle_mesh(mesh_data.path)
        o3d.visualization.draw([mesh])


.. code-block:: C++

        mesh_data = open3d::data::ArmadilloMesh();
        mesh = open3d::io::ReadTriangleMesh(mesh_data.path);
        open3d::visualization::Draw({mesh});

Mirror(s):
    - `Mirror 1 <https://github.com/isl-org/open3d_downloads/releases/download/20220201-data/ArmadilloMesh.ply>`_
Contents:
    Stanford University Computer Graphics Laboratory.
Source:
    Living Room point cloud fragment from Redwood RGB-D livingroom1 sequence.
Licence:
    Creative Commons 3.0 (CC BY 3.0).


Knot
----------------------------------------

Loading and visualizing example:

.. code-block:: Python

        mesh_data = open3d.data.KnotMesh()
        mesh = open3d.io.read_triangle_mesh(mesh_data.path)
        o3d.visualization.draw([mesh])


.. code-block:: C++

        mesh_data = open3d::data::KnotMesh();
        mesh = open3d::io::ReadTriangleMesh(mesh_data.path);
        open3d::visualization::Draw({mesh});

Mirror(s):
    - `Mirror 1 <https://github.com/isl-org/open3d_downloads/releases/download/20220201-data/fragment.ply>`_
Contents:
    fragment.ply
Source:
    Living Room point cloud fragment from Redwood RGB-D livingroom1 sequence.
Licence:
    Creative Commons 3.0 (CC BY 3.0).


RGB-D Data
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Sample NYU RGB-D Dataset Image
----------------------------------------

Loading data:

.. code-block:: Python

        rgbd_data = open3d.data.SampleRGBDImageNYU()
        color_raw = open3d.io.read_image(rgbd_data.color_path)
        depth_raw = open3d.io.read_image(rgbd_data.depth_path)


.. code-block:: C++

        rgbd_data = open3d::data::SampleRGBDImageNYU()
        color_raw = open3d::io::read_image(rgbd_data.color_path)
        depth_raw = open3d::io::read_image(rgbd_data.depth_path)

Mirror(s):
    - `Mirror 1 <https://github.com/isl-org/open3d_downloads/releases/download/20220201-data/fragment.ply>`_
Contents:
    fragment.ply
Source:
    Living Room point cloud fragment from Redwood RGB-D livingroom1 sequence.
Licence:
    Creative Commons 3.0 (CC BY 3.0).


Sample SUN RGB-D Dataset Image
----------------------------------------

Loading data:

.. code-block:: Python

        rgbd_data = open3d.data.SampleRGBDImageSUN()
        color_raw = open3d.io.read_image(rgbd_data.color_path)
        depth_raw = open3d.io.read_image(rgbd_data.depth_path)


.. code-block:: C++

        rgbd_data = open3d::data::SampleRGBDImageSUN()
        color_raw = open3d::io::read_image(rgbd_data.color_path)
        depth_raw = open3d::io::read_image(rgbd_data.depth_path)

Mirror(s):
    - `Mirror 1 <https://github.com/isl-org/open3d_downloads/releases/download/20220201-data/fragment.ply>`_
Contents:
    fragment.ply
Source:
    Living Room point cloud fragment from Redwood RGB-D livingroom1 sequence.
Licence:
    Creative Commons 3.0 (CC BY 3.0).


Sample TUM RGB-D Dataset Image
----------------------------------------

Loading data:

.. code-block:: Python

        rgbd_data = open3d.data.SampleRGBDImageTUM()
        color_raw = open3d.io.read_image(rgbd_data.color_path)
        depth_raw = open3d.io.read_image(rgbd_data.depth_path)


.. code-block:: C++

        rgbd_data = open3d::data::SampleRGBDImageTUM()
        color_raw = open3d::io::read_image(rgbd_data.color_path)
        depth_raw = open3d::io::read_image(rgbd_data.depth_path)

Mirror(s):
    - `Mirror 1 <https://github.com/isl-org/open3d_downloads/releases/download/20220201-data/fragment.ply>`_
Contents:
    fragment.ply
Source:
    Living Room point cloud fragment from Redwood RGB-D livingroom1 sequence.
Licence:
    Creative Commons 3.0 (CC BY 3.0).


Image Data
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



Demo Data
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

