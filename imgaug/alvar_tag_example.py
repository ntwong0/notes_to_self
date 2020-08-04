#!/usr/bin/env python

import os
from PIL import Image
import numpy as np
import imgaug as ia
import imgaug.augmenters as iaa
import imgaug.random as iar

# context: ar_tags/ is a directory at os.getcwd(), containing alvar tag .png files 
# alvar tags are to be presented on square faces of a regular triangular prism
# prismatize() is a front-view orthographic projection of the prism. consequentially, two faces are presented

ia.seed(123)

def prismatize(images, random_state, parents, hooks):
    ret_images = list()
    for image in images:
        val    = random_state.uniform(0.0001, 0.9999)
        aug1   = iaa.Resize({"width": val})
        image1 = aug1(images=image.reshape(1,*image.shape)).reshape(image.shape[0],-1,1)
        aug2   = iaa.Resize({"width": 1 - val})
        image2 = aug2(images=image.reshape(1,*image.shape)).reshape(image.shape[0],-1,1)
        ret_images.append(np.concatenate((image1, image2), axis=1).reshape(image.shape[0],-1,1))
    return np.stack(ret_images, axis=0).reshape(len(ret_images), *ret_images[0].shape)

def ndarray_from_filename(dirname, filename):
    return np.asarray(Image.open(dirname + "/" + filename))

def load_from_dir(dirname):
    mat = np.stack([ndarray_from_filename(dirname, fn) for fn in os.listdir(dirname)], axis=0)
    return mat.reshape(*mat.shape, 1)

aug = iaa.Lambda(prismatize)

# sanity check
for mat in [mat.reshape(mat.shape[0], mat.shape[1]) for mat in aug(images=load_from_dir("ar_tags"))]:
    Image.fromarray(mat).show()

