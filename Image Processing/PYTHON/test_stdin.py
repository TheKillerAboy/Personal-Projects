import subprocess
import os
from PIL import Image,ImageDraw

def use_cpp(file_directory,input_data, convert = int):
    data, temp = os.pipe()
    os.write(temp, bytes(' '.join(map(str,input_data)),'utf-8'))
    os.close(temp)
    s = subprocess.check_output(file_directory, stdin=data, shell=True)
    return map(convert,filter(lambda s: len(s) > 0,s.decode("utf-8").replace('\n',' ').replace('\t',' ').split(' ')))

def process_image(image_directory, tolence):
    image = Image.open(image_directory).convert("RGB")
    def pixels():
        yield image.width
        yield image.height
        yield tolence
        i,j = 0,0
        while(i < image.width and j < image.height):
            pixel = image.getpixel((i,j))
            yield pixel[0]
            yield pixel[1]
            yield pixel[2]
            i+=1
            if(i == image.width):
                i=0
                j+=1
    output =  use_cpp('../image_boarder',pixels())
    groups = next(output)
    for i in range(image.width):
        for j in range(image.height):
            next(output)
    draw = ImageDraw.Draw(image)
    for _ in range(groups):
        l,t,r,b = [next(output) for _ in range(4)]
        draw.rectangle(((l,t),(r,b)), outline="red")
    image.save(image_directory[:image_directory.rfind('.')] +'.out' +image_directory[image_directory.rfind('.'):] )


if __name__ == '__main__':
    process_image('../sublime-text_3.png',17.5)