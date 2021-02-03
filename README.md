# Image-Filters

### Image Filtering
What does it even mean to filter an image? You can think of filtering an image as taking the pixels of some original image, and modifying each pixel in such a way that a particular effect is apparent in the resulting image.

### Types of filters covered
 - Grayscale (g)
 - Reflect (r)
 - Blur (b)
 - Edge Detection (e)
 
### Steps to Compile and Run
1.  Add your images to the 'images' folder (You can also use the existing sample images)
2.  You are required to use Bitmap images ONLY
3.  Run the program for the desired filter using the following commands:
    - Grayscale:  ./filter -g images/(IMAGE_NAME).bmp grayscale.bmp
    - Reflect:  ./filter -r images/(IMAGE_NAME).bmp reflected.bmp
    - Blur:  ./filter -b images/(IMAGE_NAME).bmp blur.bmp
    - Edge Detection:  ./filter -e images/(IMAGE_NAME).bmp edge.bmp
   
