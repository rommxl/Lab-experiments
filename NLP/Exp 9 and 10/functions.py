from sentence_transformers import SentenceTransformer
from sklearn.metrics.pairwise import cosine_similarity
from spacy.matcher import Matcher
import spacy
import re


def get_similiarity(synoptic, answer):
    sentences =[synoptic, answer]
    model = SentenceTransformer('sentence-transformers/paraphrase-multilingual-MiniLM-L12-v2')
    embeddings = model.encode(sentences)
    similiarity = cosine_similarity(embeddings[0].reshape(1,-1),embeddings[1].reshape(1,-1))

    return similiarity[0][0]

def keyphrase_match_score(list_of_key_phrases: list[str], answer: str):
    nlp = spacy.load('en_core_web_sm')
    score = 0
    
    for phrase in list_of_key_phrases:
        phrase = re.sub(r'[^a-zA-z0-9 ]',' ',phrase)
        phrase = re.sub(r'\s+',' ',phrase)

        m_tool = Matcher(nlp.vocab)

        vocab = [{'LOWER':word} for word in phrase.split()]
        m_tool.add('matcher',[vocab,])
        sentence = nlp(answer)
        if len(m_tool(sentence)) > 0:
            score+=1


    return score/len(list_of_key_phrases)

def evaluate(evaluation: str, synoptic: list[str] | str, submitted: str, marks: int):
    score_factor = None
    
    if(evaluation == 'keyword'):
        score_factor = keyphrase_match_score(synoptic.split(','),submitted)
    
    elif(evaluation == 'subjective'):
        score_factor = get_similiarity(synoptic, submitted)

    return marks * score_factor