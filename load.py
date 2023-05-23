from pynq import Overlay
from pynq import MMIO
from time import sleep
ol = Overlay("/home/xilinx/pynq_code/motor_driver.bit")
ol.download()
