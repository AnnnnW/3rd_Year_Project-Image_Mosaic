# 3rd Year Project- the Image Mosaic
This is my third year project in the University of Manchester.
There are three parts to process the image:
  * Image Analysor
  * Image Cutter
  * Tiler
  
I call the original image, target image, and for the small pieces to replace is tiles.
  
  The image Analysor should do these work:
  - read the images and their names from the directory and write the name into a file
  - tile images with their average colour and save them in the file,
  - rezise them with the required size,
  - read the file and read the data saved in
  
  The image cutter should do these work:
  - ead the target file 
  - cut the image using a 9x9 filter
  - make the 9x9 blocks to be mosaic by using the average RGB colour of the 81 pixels
  
  The tiler should do these work:
  - Read from the file which saved the name and the average colour for each tile images
  - Compare each average colour with each 9x9 piece
  - replace the piece with the most similar colour tile

And after finishing the basic version of this project which can achieve target image cut into 9x9 pieces, the analysor gives the correct average colours of the tiles and replace with the 9x9 pieces,
I will do following improvements:

for the tiler:
  * it can also do the colour correction to make the tile more similar to the original piece
  * implement a better algorithm to choose the most silimar tile
      - can reduce the replication among tiles
      - can deal with three best choices. Example: how to choose among: all light blue, half white half dark blue, white background with dark blue dots and so on, which all have the same average colour: light blue.
