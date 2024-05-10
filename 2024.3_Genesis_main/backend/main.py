from typing import Union
from model3 import generate, additional
import os
import json
from fastapi import FastAPI, File, UploadFile
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel
app = FastAPI()

# Add middleware for CORS
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],  # Set this to your frontend URL or '*' for any origin
    allow_credentials=True,
    allow_methods=["GET", "POST", "PUT", "DELETE", "OPTIONS"],  # Add the HTTP methods you want to allow
    allow_headers=["*"],  # Set this to the headers you want to allow or '*' for any header
)


#@app.get("/")
def read_root():
    return {"Hello": "World"}

@app.get('/categories')
def get_categories():
    return ["first_aid", "personal", "workplace", "chemical", "report_incident"]

class Item(BaseModel):
    incorrect: list

@app.post('/feedback')
async def feedback(body: Item):
    wrong_questions = body.incorrect
    response_info = []
    additional_info = additional(wrong_questions)

    response_texts = []
    for response in additional_info:
         response_texts.append(response.text)
                               #.replace('\n', '').replace('\\', '').replace('para', '').strip())
    print(response_texts)
    #response_info.extend(response_texts)  # Use extend to avoid nested lists
    
    return json.dumps({"responses": response_texts})
    #     response_info.append(response_texts)
    # return json.loads(''.join(additional_info))    

@app.get('/questions/{category}')
def get_questions(category):
    #create a dict   
    dict_file = {"first_aid": "first aid.pdf", "personal": "personal protection.pdf",
                 "workplace": "workplace.pdf", "chemical": "chemical.pdf",
                 "report_incident": "report incident.pdf"}
    filename = dict_file.get(category) #find the file using key
    # Read the file contents
    with open(f"./categories/{filename}", "rb") as file:
        file_contents = file.read()

    # Generate responses (Replace this with your own generate function)
    # Assuming responses is a list of generated responses
    responses = generate(file_contents)  # Call your generate function with file contents
    
    response_texts = []
    for response in responses:
        response_texts.append(response.text)
    
    # Return the response as JSON
    return json.loads(''.join(response_texts))

@app.get("/items/{item_id}")
def read_item(item_id: int, q: Union[str, None] = None):
    return {"item_id": item_id, "q": q}
