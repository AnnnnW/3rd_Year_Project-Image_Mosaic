# 3rd Year Project- the Image Mosaic
This is my third year project in the University of Manchester. The language using is C++ and OpenCV package is used to help with image processing.

There are three parts to generate the image mosaic:
  * Image Analysor
  * Image Cutter
  * Tiler
  
There are three kinds of images in the project: target image is called as the original input image, tiles for the small image pieces to replace, and result image for output image.
  
  The Image Analyser should do these work:
  - read tile images and calculate their average colours then save them into a file,
  - rezise the tiles into a required size,
  - read the file and save the data into an array
  
  The Image Cutter should:
  - read the target file 
  - cut the image into a 9x9 block
  - mosaic the 9x9 blocks to by using the average RGB colour of the block
  
  The Tiler should do these work:
  - get all the data calculate in the Image Cutter and the Image Analyser
  - compare the average colour between the blocks and the tiles
  - replace the certain block with the its most colour-similar tile image
  - output the result image mosaic

This version is the basic image mosaic generator which can only produce 9x9 block-size image mosaic.
There are some improvements in the GUI version (see: https://github.com/AnnnnW/ImageMosaicGUI):

* There are no output data file to store the average colours and the image infos. All data is in arrays.
* A GUI is implemented via Qt package, which can only compatible in MacOS system.
* The target image and the tile images can be choosed by user, and the path of the images can be seen.
* A quickview window of the target image and a preview window of the result image is enabled.
* The result image can be saved in a certain directory.
* The block size is more flexible, there provides several sizes.
* An adjustable target image overlay-level is provide.
* Provide the Unequal-block-size result (still buggy)
* TBC...
