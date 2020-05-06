## Dr. Brenner's SLAM Lectures Implemented in Modern Python. ##
Code heavily inspired and using code from https://github.com/patrick--/SLAM-Exploration/blob/master/
To install and setup:
<ul>
    <li> git clone https://github.com/chancecardona/SLAM.git </li>
    <li> cd SLAM/ </li>
    <li> git init submodule </li>
    <li> git submodule update </li>
    <li> mkdir build </li>
    <li> cd build/ </li>
    <li> cmake .. </li>
    <li> make </li>
</ul>
If there are errors with numpy/arrayobject.h first make sure python2.7 and python2.7-numpy are installed on your system and then if error persists run:
<ul>
    Ubuntu:
    <li> sudo ln -s /usr/lib/python2.7/dist-packages/numpy/core/include/numpy /usr/include/numpy </li>
    Arch:
    <li> sudo ln -s /usr/lib/python2.7/site-packages/numpy/core/include/numpy /usr/include/numpy </li>
</ul>
