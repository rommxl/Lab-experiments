import praw
from vaderSentiment.vaderSentiment import SentimentIntensityAnalyzer
from datetime import datetime, timedelta

# Initialize Reddit API wrapper
reddit = praw.Reddit(client_id='YOUR_CLIENT_ID',
                     client_secret='YOUR_CLIENT_SECRET',
                     user_agent='YOUR_USER_AGENT')

# Define topic keyword
topic_keyword = "climate change"

# Define start and end dates for the time span
start_date = datetime(2024, 1, 1)  # Example: January 1st, 2024
end_date = datetime(2024, 4, 1)    # Example: April 1st, 2024

# Fetch submissions containing the topic keyword within the specified time range
submissions = reddit.subreddit("all").search(topic_keyword, time_filter='month', sort='new')

# Initialize sentiment analyzer
analyzer = SentimentIntensityAnalyzer()

# List to store sentiment scores
sentiment_scores = []

# Iterate through submissions and analyze sentiment of titles and comments
for submission in submissions:
    # Convert submission creation time to datetime object
    submission_time = datetime.utcfromtimestamp(submission.created_utc)
    
    # Check if submission is within the specified time range
    if start_date <= submission_time <= end_date:
        title_sentiment = analyzer.polarity_scores(submission.title)['compound']
        sentiment_scores.append(title_sentiment)

        # Analyze sentiment of comments
        submission.comments.replace_more(limit=None)
        for comment in submission.comments.list():
            comment_time = datetime.utcfromtimestamp(comment.created_utc)
            if start_date <= comment_time <= end_date:
                comment_sentiment = analyzer.polarity_scores(comment.body)['compound']
                sentiment_scores.append(comment_sentiment)

# Calculate overall sentiment score
overall_sentiment_score = sum(sentiment_scores) / len(sentiment_scores)
print("Overall sentiment score:", overall_sentiment_score)
