type state = {
  items: list(TodoModel.item),
  inputText: string,
};

type action =
  | InputText(string)
  | Toggle(int)
  | RemoveAll
  | RemoveItem(int)
  | RemoveCompleted
  | Submit;

let component = ReasonReact.reducerComponent("TodoApp");

let str = ReasonReact.string;

let make = _children => {
  let handleSubmit = state => {
    let newId: int = List.length(state.items);
    let newItem: TodoModel.item = {
      id: newId,
      title: state.inputText,
      completed: false,
    };
    let newList = [newItem, ...state.items];
    ReasonReact.Update({items: newList, inputText: ""});
  };
  {
    ...component,
    initialState: () => {
      items: [{id: 0, title: "milk", completed: false}],
      inputText: "",
    },
    reducer: action =>
      switch (action) {
      | InputText(newText) => (
          state => ReasonReact.Update({...state, inputText: newText})
        )
      | Toggle(id) => (
          state =>
            ReasonReact.Update({
              ...state,
              items:
                List.map(
                  (item: TodoModel.item) =>
                    item.id == id ?
                      {
                        ...item,
                        TodoModel.completed: ! TodoModel.(item.completed),
                      } :
                      item,
                  state.items,
                ),
            })
        )
      | RemoveItem(id) => (
          state =>
            ReasonReact.Update({
              ...state,
              items:
                List.filter(
                  (item: TodoModel.item) => item.id !== id,
                  state.items,
                ),
            })
        )
      | RemoveCompleted => (
          state =>
            ReasonReact.Update({
              ...state,
              items:
                List.filter(
                  (item: TodoModel.item) => ! item.completed,
                  state.items,
                ),
            })
        )
      | Submit => (state => handleSubmit(state))
      | RemoveAll => (state => ReasonReact.Update({...state, items: []}))
      },
    render: self => {
      let {items, inputText} = self.state;
      <div className="app">
        <TodoHeader />
        <AddTodo
          submit=((_) => self.send(Submit))
          value=inputText
          onInputText=(text => self.send(InputText(text)))
        />
        <div className="list">
          (
            ReasonReact.array(
              Array.of_list(
                List.map(
                  (item: TodoModel.item) =>
                    <TodoItem
                      key=(string_of_int(item.id))
                      item
                      onRemove=(id => self.send(RemoveItem(id)))
                      onToggle=(id => self.send(Toggle(id)))
                    />,
                  items,
                ),
              ),
            )
          )
        </div>
        <TodoFooter
          itemCount=(List.length(items))
          onRemoveAll=((_) => self.send(RemoveAll))
          onRemoveCompleted=((_) => self.send(RemoveCompleted))
        />
      </div>;
    },
  };
};