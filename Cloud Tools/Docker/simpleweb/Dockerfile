FROM node:alpine 
WORKDIR /usr/myApps/simpleWeb
COPY ./package.json ./
RUN npm install
COPY ./ ./
CMD [ "npm","start" ]