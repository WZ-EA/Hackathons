import base64
import vertexai
from vertexai.generative_models import GenerativeModel, Part, FinishReason
import vertexai.preview.generative_models as generative_models


def generate(file_contents):
  vertexai.init(project="virtual-core-418819", location="us-central1")
  model = GenerativeModel("gemini-1.0-pro-vision-001")
  text1 = """generate 10 multiple questions in json format following this schema [{"question: String, "options": String[], "answer": String}]"""
  document1 = Part.from_data(mime_type="application/pdf",
    data=file_contents)
  responses = model.generate_content(
      [text1, document1],
      #generation_config=generation_config,
      #safety_settings=safety_settings,
      stream=True,
  )

  return responses

import os
os.environ["GOOGLE_APPLICATION_CREDENTIALS"]="key.json"

def additional(wrong_questions):
  vertexai.init(project="virtual-core-418819", location="us-central1")
  model = GenerativeModel("gemini-1.0-pro-vision-001")
  text1 = """The user got the {wrong_questions} wrong, generate 90 words for the student engineer or employee 
          to learn more about these safety topic, return in text format"""
          #json format following this schema [{"para": String}]
  responses = model.generate_content(
    [text1],
    stream=True,
  )
  return responses