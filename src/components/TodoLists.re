type state = {
  items: list(TodoModel.item),
  inputText: string,
};

type action =
  | InputText(string)
  | DeleteAll
  | Submit;

let component = ReasonReact.reducerComponent("TodoLists");

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
      | Submit => (state => handleSubmit(state))
      | DeleteAll => (state => ReasonReact.Update({...state, items: []}))
      },
    render: self => {
      let {items, inputText} = self.state;
      Js.log(inputText);
      let numItems = List.length(items);
      let word = numItems === 1 ? " item" : "items";
      <div className="app">
        <div>
          <input
            value=inputText
            placeholder="add item"
            onChange=(
              event =>
                self.send(
                  InputText(
                    ReactDOMRe.domElementToObj(
                      ReactEventRe.Form.target(event),
                    )##value,
                  ),
                )
            )
          />
          <button onClick=((_) => self.send(Submit))> (str("Add")) </button>
        </div>
        <div className="item">
          (
            ReasonReact.array(
              Array.of_list(
                List.map(
                  (item: TodoModel.item) =>
                    <TodoItem key=(string_of_int(item.id)) item />,
                  items,
                ),
              ),
            )
          )
        </div>
        <div className="footer">
          <button onClick=((_) => self.send(DeleteAll))>
            (str("Delete All"))
          </button>
          <p> (str(string_of_int(numItems) ++ word)) </p>
        </div>
      </div>;
    },
  };
};