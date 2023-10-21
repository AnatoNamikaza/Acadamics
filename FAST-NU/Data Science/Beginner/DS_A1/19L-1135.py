import requests
from bs4 import BeautifulSoup
import pandas as pd

URL = "http://lhr.nu.edu.pk/faculty/"
r = requests.get(URL)
content = r.content
soup = BeautifulSoup(content,'html.parser')

dept = ['fsc', 'ee', 'cv', 'fsm', 'ss']
faculty = [] 

#   -   -   -   -   -   -   Step-1   -   -   -   -   -   -   -

[faculty.append(soup.find('div',id=dp).findAll('div',class_='card')) for dp in dept]

NU = 'http://lhr.nu.edu.pk/'

def dataframe_maker_1(faculty):
    ID, facultyURL, email, name, image, designation, HECApproved = [], [], [], [], [], [], []

    for f in faculty:
        ID.append(f.find('a',class_='faculty-link')['href'].split('/')[-1])
        facultyURL.append(NU+f.find('a',class_='faculty-link')['href'])
        email.append(f.find('p',class_='mb-0').text.strip())
        name.append(f.find('h5',class_='text-center').text.strip())
        designation.append(f.find('p',class_='small').text.strip().split('\n')[0])
        HECApproved.append((f.find('p',class_='small').text.find('HEC Approved PhD Supervisor') >-1))
        image.append(NU+f.find('img',class_='card-img-top')['src'])

    return pd.DataFrame({
        'ID':ID,
        'name':name,
        'designation':designation,
        'HEC Approved PhD Supervisor': HECApproved,
        'email':email,
        'facultyURL':facultyURL,
        'image':image
    })

[dataframe_maker_1(faculty[i]).to_csv(dept[i]+'.csv') for i in range(len(dept))]

#   -   -   -   -   -   -   Step-2   -   -   -   -   -   -   -

samples, ids_list = [], []

[samples.append(pd.read_csv(dept[i]+'.csv').sample(frac=0.1)) for i in range(len(dept))]

[ids_list.append(s['ID']) for s in samples]

def dataframe_maker_2(dept, ids):
    Extension, Education = [], []

    for i in ids:
        soup = BeautifulSoup(requests.get("http://lhr.nu.edu.pk/"+dept+"/facultyProfile/"+str(i)).content,'html.parser')
        val = soup.find('div',class_='col-lg-8').find('ul')
        if len(val.contents) > 1:
            Education.append(val.contents[1].text.strip())
        else:
            Education.append("")
        Extension.append(soup.find('div',class_='card').find('p',class_='mt-0').text.strip())
        
    return pd.DataFrame({
        'ID':ids,
        'Extension':Extension,
        'Education':Education
    })

[dataframe_maker_2(dept[i],ids_list[i]).to_csv(dept[i]+'_2.csv') for i in range(len(dept))]

#   -   -   -   -   -   -   Step-3   -   -   -   -   -   -   -

samples = []
[samples.append(pd.read_csv(dept[i]+'.csv')) for i in range(len(dept))]

samples_2 = []
[samples_2.append(pd.read_csv(dept[i]+'_2.csv')) for i in range(len(dept))]

merged_samples = []
[merged_samples.append(pd.merge(samples[i].drop(samples[i].columns[0], axis =1), samples_2[i].drop(samples_2[i].columns[0], axis =1), on='ID', how='left')) for i in range(len(dept))]

pd.concat(merged_samples).reset_index().to_csv("fast_lhr_faculty.csv")