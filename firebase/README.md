### Sample firebase webhook publishing

Using the Particle CLI, you can create the event with:

    particle webhook create firebase_post.json

You can test pushing data to the firebase with:

    particle publish firebase_post "{ \"my_data\" : \"test\" }"

You can see the results in realtime being pushed to the root of the firebase
