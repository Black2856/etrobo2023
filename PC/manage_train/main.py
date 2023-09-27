import requests
import time
from ..manage_signal.competitionSystem import CompetitionSystem

if(__name__ == "__main__"):
    cs = CompetitionSystem()
    cs.setCourse("test")
    t = 1000
    cs.IoT_SET(50)
    for i in range(t):
        cs.IoT_GET()

        time.sleep(500/1000)
    cs.IoT_SET(0)